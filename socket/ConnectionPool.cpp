#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <time.h>
#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <vector>
#include "ConnectionPool.h"
#include "SocketException.h"

using namespace std;



CConnPool::CConnPool(string server_addr, int port, int poolLen )
{

    if (poolLen <= 0)
        return;
    m_serverAddr = server_addr;
    m_port = port;
    m_poolLen = poolLen;
	if( pthread_mutex_init(&m_work_mutex, NULL))
	{
		cerr << "Mutex initialization failed." <<endl;
		exit (EXIT_FAILURE);
	}

    int i;
    for(i=0; i<m_poolLen; ++i)
    {
        try
        {
            ClientSocket *client_socket = new ClientSocket(m_serverAddr, m_port);
            m_vectorConn.push_back(client_socket);
            m_mapVI[client_socket] = i;
        }
        catch(SocketException &e)
        {
            cout << "Exception was caught:" << e.description() << endl;
        }
    }
}
CConnPool::~CConnPool( )
{
}

ClientSocket* CConnPool::getOneConn()
{
	int i;
	pthread_mutex_lock(&m_work_mutex);
    for(i=0; i<m_poolLen; ++i)
    {
        ClientSocket *client_socket = m_vectorConn[i];
        if(client_socket->m_isDead)
        {
            //client_socket->Close();
            client_socket = new ClientSocket(m_serverAddr, m_port);
            m_vectorConn.push_back(client_socket);
            m_mapVI[client_socket] = i;
        }
        if(client_socket != NULL && client_socket->m_isFree && !client_socket->m_isDead)
        {
            return client_socket;
        }

    }
	pthread_mutex_unlock(&m_work_mutex);

    return NULL;
}

void  CConnPool::freeOneConn(ClientSocket* pConn)
{
    map<ClientSocket*, int>::iterator iter;

	pthread_mutex_lock(&m_work_mutex);
    iter = m_mapVI.find(pConn);
    if(iter == m_mapVI.end())
    {
        cout << "free One Connection  failed" << endl;
        return;
    }
    int index = iter->second;
    m_vectorConn[index]->m_isFree = true;
    m_vectorConn[index]->m_isDead = false;
    cout << "free One Connection succeed." << endl;
	pthread_mutex_unlock(&m_work_mutex);
}

