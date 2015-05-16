// Implementation of the ServerSocket class
#include "../include/socket/ServerSocket.h"
#include "../include/socket/SocketException.h"
using namespace std;

ServerSocket::ServerSocket ( )
{
    /*
        if ( ! Socket::create() )
        {
            throw SocketException ( "Could not create server socket." );
        }

        if ( ! Socket::bind ( port ) )
        {
            throw SocketException ( "Could not bind to port." );
        }

        if ( ! Socket::listen() )
        {
            throw SocketException ( "Could not listen to socket." );
        }
    	*/

    m_listen_sock = 0;
    m_epoll_fd = 0;
    m_max_count = 0;
    m_epoll_events = NULL;

}

ServerSocket::~ServerSocket()
{
    if (m_listen_sock > 0)
    {
        close(m_listen_sock);
    }

    if (m_epoll_fd > 0)
    {
        close(m_epoll_fd);
    }

}

bool ServerSocket::init(int port , int sock_count)
{
    m_max_count = sock_count;

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(&server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    m_listen_sock = ::socket(AF_INET, SOCK_STREAM, 0);
    if(m_listen_sock == -1)
    {
        cout << "creat socket error" <<endl;
        exit(1);
    }

    if(::bind(m_listen_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
    {
        cout << "bind socket error" <<endl;
        exit(1);
    }

    if(::listen(m_listen_sock, 5) == -1)
    {
        cout << "listen socket error" <<endl;
        exit(1);
    }
    /*
    if ( ! Socket::create() )
    {
        throw SocketException ( "Could not create server socket." );
    }

    if ( ! Socket::bind ( port ) )
    {
        throw SocketException ( "Could not bind to port." );
    }

    if ( ! Socket::listen() )
    {
        throw SocketException ( "Could not listen to socket." );
    }
    */

    m_epoll_events = new struct epoll_event[sock_count];
    if (m_epoll_events == NULL)
    {
        cout << "m_epoll_events error"<<endl;
        exit(-1);
    }

    m_epoll_fd = epoll_create(sock_count);
    struct epoll_event ev;
    ev.data.fd = m_listen_sock;
    ev.events  = EPOLLIN;
    epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, m_listen_sock, &ev);
}

bool ServerSocket::init(const char* ip, int port , int sock_count)
{
    m_max_count = sock_count;
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(&server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    m_listen_sock = ::socket(AF_INET, SOCK_STREAM, 0);
    if(m_listen_sock == -1)
    {
        exit(1);
    }

    if(::bind(m_listen_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
    {
        exit(1);
    }

    if(::listen(m_listen_sock, 5) == -1)
    {
        exit(1);
    }

    m_epoll_events = new struct epoll_event[sock_count];
    if (m_epoll_events == NULL)
    {
        exit(1);
    }

    m_epoll_fd = epoll_create(sock_count);
    struct epoll_event ev;
    ev.data.fd = m_listen_sock;
    ev.events  = EPOLLIN;
    epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, m_listen_sock, &ev);
}

int ServerSocket::accept_new_client()
{
    sockaddr_in client_addr;
    memset(&client_addr, 0, sizeof(client_addr));
    socklen_t clilen = sizeof(struct sockaddr);
    int new_sock = ::accept(m_listen_sock, (struct sockaddr*)&client_addr, &clilen);


    struct epoll_event ev;
    ev.data.fd = new_sock;
    ev.events  = EPOLLIN;
    epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, new_sock, &ev);
    return new_sock;
}

int ServerSocket::send_data(int sock, char* send_buf, int buf_len)
{
    int len = 0;
    int ret = 0;
    while(len < buf_len)
    {
        ret = ::send(sock, send_buf + len, 1024, 0);
        if(ret <= 0)
        {
            struct epoll_event ev;
            ev.data.fd = sock;
            ev.events  = EPOLLERR;
            epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, sock, &ev);
            close(sock);
            break;
        }
        else
        {
            len += ret;
        }

        if(ret < 1024)
        {
            break;
        }
    }

    if(ret > 0)
    {
        struct epoll_event ev;
        ev.data.fd = sock;
        ev.events  = EPOLLIN;
        epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, sock, &ev);
    }

    return ret <= 0 ? ret : len;
}

const ServerSocket& ServerSocket::operator << ( const std::string& s ) const
{
    if ( ! Socket::send ( s ) )
    {
        throw SocketException ( "Could not write to socket." );
    }

    return *this;

}


int ServerSocket::recv_data(int sock, char* recv_buf)
{
    char buf[1024] = {0};
    int len = 0;
    int ret = 0;
    while(ret >= 0)
    {
        ret = ::recv(sock, buf, sizeof(buf), 0);
        if(ret <= 0)
        {
            struct epoll_event ev;
            ev.data.fd = sock;
            ev.events  = EPOLLERR;
            epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, sock, &ev);
            close(sock);
            break;
        }
        else if(ret < 1024)
        {
            memcpy(recv_buf, buf, ret);
            len += ret;
            struct epoll_event ev;
            ev.data.fd = sock;
            ev.events  = EPOLLOUT;
            epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, sock, &ev);
            break;
        }
        else
        {
            memcpy(recv_buf, buf, sizeof(buf));
            len += ret;
        }
    }

    return ret <= 0 ? ret : len;
}


const ServerSocket& ServerSocket::operator >> ( std::string& s ) const
{
    if ( ! Socket::recv ( s ) )
    {
        throw SocketException ( "Could not read from socket." );
    }

    return *this;
}

int ServerSocket::epoll_server_wait(int time_out)
{
    return epoll_wait(m_epoll_fd, m_epoll_events, m_max_count, time_out);
}

void ServerSocket::run(int time_out)
{
    char *recv_buf = new char[65535];
    char *send_buf = new char[65535];
    int ret;
    while(1)
    {
        int ret = epoll_server_wait(time_out);
        if(ret == 0)
        {
            cout<<"time out"<<endl;
            continue;
        }
        else if(ret == -1)
        {
            cout<<"error"<<endl;
        }
        else
        {
            for(int i = 0; i < ret; i++)
            {
                if(m_epoll_events[i].data.fd == m_listen_sock)
                {
                    if(m_epoll_events[i].events & EPOLLIN)
                    {
                        int new_sock = accept_new_client();
                    }
                }
                else
                {
                    if(m_epoll_events[i].events & EPOLLIN)
                    {
                        int recv_count = recv_data(m_epoll_events[i].data.fd, recv_buf);
                        cout<<recv_buf<<endl;
                        strcpy(send_buf, recv_buf);
                        memset(recv_buf, 0, sizeof(recv_buf));
                    }
                    else if(m_epoll_events[i].events & EPOLLOUT)
                    {
                        int send_count = send_data(m_epoll_events[i].data.fd, send_buf, strlen(send_buf));
                        memset(send_buf, 0, sizeof(send_buf));
                    }

                }
            }
        }
    }
}

void ServerSocket::accept ( ServerSocket& sock )
{
    if ( ! Socket::accept ( sock ) )
    {
        throw SocketException ( "Could not accept socket." );
    }
}
