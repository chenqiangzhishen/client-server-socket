#include "ServerSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>
using namespace std;

int main ( void )
{
    std::cout << "running....\n";

    try
    {
        // Create the socket
        ServerSocket server ( 33333 );

        while ( true )
        {

            ServerSocket new_sock;
            server.accept ( new_sock );

            try
            {
                while ( true )
                {
                    std::string data;
                    new_sock >> data;
                    new_sock << data;
                }
            }
            catch ( SocketException& ) {}

        }
    }
    catch ( SocketException& e )
    {
        std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }

    return 0;
}
