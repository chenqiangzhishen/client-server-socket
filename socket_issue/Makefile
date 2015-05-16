# Makefile for the socket 
#

server_objects = ServerSocket.o Socket.o ServerMain.o
client_objects = ClientSocket.o Socket.o ConnectionPool.o ClientMain.o
#conn_pool_objects = ConnectionPool.o


all : server client

server: $(server_objects)
	g++ -o server $(server_objects)


client: $(client_objects)
	g++ -o client $(client_objects)  -lpthread


Socket: Socket.cpp
ServerSocket: ServerSocket.cpp
ClientSocket: ClientSocket.cpp 
ServerMain: ServerMain.cpp
ClientMain: ClientMain.cpp ConnectionPool.cpp
ConnectionPool: ConnectionPool.cpp ClientSocket.cpp


clean:
	rm -f *.o server client
