#ifndef __CONNECTION_POOL_H__
#define __CONNECTION_POOL_H__
#include "semaphore.h"
#include "ClientSocket.h"
#include <vector>
#include <map>

using namespace std;

class CConnPool
{
public:
    CConnPool(string server_addr, int port, int pool_len);
    ~CConnPool();
    ClientSocket* getOneConn(); //从连接池取一个连接
    void  freeOneConn(ClientSocket* pConn);// 连接用完了，把它放回连接池。以便其他人用。

private:
    string m_serverAddr;
    int m_port;
    int m_poolLen;
	pthread_mutex_t m_work_mutex;
    vector<ClientSocket*>  m_vectorConn;
    map<ClientSocket*, int> m_mapVI; //  从连接的地址，快速找到索引，便于存放到m_vectorconn中。

};

#endif

