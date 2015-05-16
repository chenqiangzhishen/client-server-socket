// Definition of the ServerSocket class

#ifndef ServerSocket_class
#define ServerSocket_class
#include  <stdio.h>
#include <stdlib.h>
#include  <iostream>
#include <string.h>
#include  <unistd.h>
#include  <fcntl.h>
#include  <errno.h>
#include  <sys/types.h>
#include  <sys/socket.h>
#include <pthread.h>
#include  <sys/epoll.h>
#include "Socket.h"


class ServerSocket : private Socket
{
public:

    ServerSocket ();
    virtual ~ServerSocket();

    const ServerSocket& operator << ( const std::string& ) const;
    const ServerSocket& operator >> ( std::string& ) const;

    void accept ( ServerSocket& );
/////////////////////////
public:
    bool init(int port, int sock_count);
    bool init(const char* ip, int port, int sock_count);
    int epoll_server_wait(int time_out);
    int accept_new_client();
    int recv_data(int sock, char* recv_buf);
    int send_data(int sock, char* send_buf, int buf_len);
    void run(int time_out);

private:
    int m_listen_sock;
    int m_epoll_fd;
    int m_max_count;
    struct epoll_event *m_epoll_events;
};


#endif
