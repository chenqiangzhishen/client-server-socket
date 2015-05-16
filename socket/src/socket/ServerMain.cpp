#include "../include/socket/ServerSocket.h"
#include "../include/socket/SocketException.h"
#include <iostream>
#include <string>
#include <sys/epoll.h>


using namespace std;

int main ( void )
{
    std::cout << "running....\n";

    try
    {
        ServerSocket my_epoll;
        my_epoll.init(33333, 10);
       // my_epoll.init("127.0.0.1", 33333, 10);
        my_epoll.run(4000);
    }

    catch ( SocketException& e )
    {
        std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }

    return 0;
}
