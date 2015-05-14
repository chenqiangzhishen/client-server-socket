# Makefile for the socket programming example
#

server_objects = ServerSocket.o Socket.o ServerMain.o
client_objects = ClientSocket.o Socket.o ClientMain.o


all : server client

server: $(server_objects)
	g++ -o server $(server_objects)


client: $(client_objects)
	g++ -o client $(client_objects)


Socket: Socket.cpp
ServerSocket: ServerSocket.cpp
ClientSocket: ClientSocket.cpp
ServerMain: ServerMain.cpp
ClientMain: ClientMain.cpp


clean:
	rm -f *.o server client