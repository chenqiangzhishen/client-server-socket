#include "ClientSocket.h"
#include "json/json.h"
#include "SocketException.h"
#include "ConnectionPool.h"
#include <iostream>
#include <string>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include "sm.SocketMessage.pb.h"
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/logger.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/layout.h>
#include <log4cplus/loggingmacros.h>
using namespace std;
using namespace log4cplus;

const string kServer_Address = "127.0.0.1";
const int port = 33333;
const int poolLen = 5;
int exit_flag = 1;


char filename[50];
Logger pSocketLogger;
SharedAppenderPtr pFileAppender;

pthread_mutex_t log_mutex;

void writelog(char* leval,char* info)
{
    struct tm *p;
    time_t lt = time(NULL);
    p = localtime(&lt);
    char* timetemp = ctime(&lt);
    *(timetemp + strlen(timetemp)-1) = '\0';
    char temp[10000];
    sprintf(temp, "[%s] %s", timetemp, info);
    //printf("temp==%s",temp);
    //printf("leval====%s ",leval);
    if(memcmp(leval, "TRACE", 5)==0)
        // printf("%d===%d",memcmp("TRACE","TRAC1E",5),memcmp(leval,"TRACE",5));
        LOG4CPLUS_TRACE(pSocketLogger, temp);
    if(memcmp(leval,"DEBUG", 5) == 0)
        LOG4CPLUS_DEBUG(pSocketLogger, temp);
    if(memcmp(leval,"INFO", 4) == 0)
        LOG4CPLUS_INFO(pSocketLogger, temp);
    if(memcmp(leval,"WARN", 4) == 0)
        LOG4CPLUS_WARN(pSocketLogger, temp);
    if(memcmp(leval,"ERROR", 5) == 0)
        LOG4CPLUS_ERROR(pSocketLogger, temp);
    if(memcmp(leval,"FATAL", 5) == 0)
        LOG4CPLUS_FATAL(pSocketLogger, temp);
}

void *thread_function(void *arg)
{
    stringstream ss;
    string s;
    Json::Value root;
    string send_str;
    srand((unsigned)time(NULL));

    while(exit_flag)
    {
        cout << "send Json to server." << endl;
        try
        {

            CConnPool *client_pool = new CConnPool (kServer_Address, port, poolLen);
            ClientSocket *client_socket = client_pool->getOneConn();

            //request JSON format from server.
            root["key_id"] = rand();
            send_str = root.toStyledString();
            cout << send_str <<endl;
            std::string reply;

            try
            {
                *client_socket << send_str;
                *client_socket >> reply;
            }
            catch ( SocketException& ) {}

            //receive protobuf format data from server.
            sm::SocketMessage sockMessage;
            sockMessage.ParseFromString(reply);
            int recv_key_id = sockMessage.received_key_id_plus_1();
            ss << recv_key_id;
            s = "value :" + ss.str();
            cout << "We received this response from the server:\n" <<  s << endl;;

            //add logs
            pthread_mutex_lock(&log_mutex);
            pFileAppender = new FileAppender((filename));
            pSocketLogger = Logger::getInstance(("LoggerName"));
            pSocketLogger.addAppender(pFileAppender);
            writelog("TRACE", const_cast<char*>(s.c_str()));
            writelog("DEBUG", const_cast<char*>(s.c_str()));
            writelog("ERROR", const_cast<char*>(s.c_str()));
            pthread_mutex_unlock(&log_mutex);

            ss.clear();
            ss.str("");

        }
        catch ( SocketException& e )
        {
            cout << "Exception was caught:" << e.description() << "\n";
            exit(EXIT_FAILURE);
        }

        sleep(1);
    }
    cout << "every 1 second request thread exit." << endl;
    pthread_exit(0);
}

int main ( void )
{
    FILE* stream=fopen(filename,"wb+");
    struct tm *p;
    time_t lt = time(NULL);
    p = localtime(&lt);
    sprintf(filename, "%d-%d-%d.txt", (1900+p->tm_year), (1+p->tm_mon), p->tm_mday);
    pthread_t thread;


    if(0 != pthread_mutex_init(&log_mutex, NULL))
    {
        cerr << "log mutex initialization failed" << endl;
        exit(EXIT_FAILURE);
    }

    if(0 != pthread_create(&thread, NULL, thread_function, NULL))
    {
        cerr << "Thread creation failed" << endl;
        exit(EXIT_FAILURE);
    }

    char ch;
    while(cin>>ch)
    {
        if (ch == 'q')
            exit_flag = 0;
        cin.clear();
    }
    cout << "Terminate the thread now." << endl;

    cout << "Wait for thread to exit" << endl;

    pthread_join(thread, NULL);
    cout << "Bye!!" << endl;

    return 0;
}
