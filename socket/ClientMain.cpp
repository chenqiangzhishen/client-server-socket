#include "ClientSocket.h"
#include "SocketException.h"
#include "ConnectionPool.h"
#include <iostream>
#include <string>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;
const string kServer_Address = "localhost";
const int port = 33333;
const int poolLen = 5;
int exit_flag = 1;

void *thread_function(void *arg)
{
    while(exit_flag)
    {
        cout << "send Json to server." << endl;
        try
        {

            //ClientSocket client_socket ( "localhost", 30000 );
			CConnPool *client_pool = new CConnPool (kServer_Address, port, poolLen);
			ClientSocket *client_socket = client_pool->getOneConn();	
			

            std::string reply;

            try
            {
                *client_socket << "Test message.";
                *client_socket >> reply;
            }
            catch ( SocketException& ) {}

            cout << "We received this response from the server:\n\"" << reply << "\"\n";;

        }
        catch ( SocketException& e )
        {
            cout << "Exception was caught:" << e.description() << "\n";
        }

        sleep(1);
    }
    cout << "every 1 second request thread exit." << endl;
}

int main ( void )
{
    pthread_t thread;

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
