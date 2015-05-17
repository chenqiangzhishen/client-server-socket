# Makefile for the socket 
#

CC = g++
CFLAGS = -g

server_objects = ServerSocket.o Socket.o ServerMain.o sm.SocketMessage.pb.o
client_objects = ClientSocket.o Socket.o ConnectionPool.o ClientMain.o sm.SocketMessage.pb.o
#conn_pool_objects = ConnectionPool.o
#INCLUDES=/home/cq/jsoncpp/

all : server client

server: $(server_objects)
	$(CC) -o server $(server_objects) -ljson -lpthread -lprotobuf
#$(CC) -o server $(server_objects)  /home/cq/jsoncpp/lib/libjson.a  -lpthread -lprotobuf


client: $(client_objects)
	$(CC) -o client $(client_objects) -ljson  -lpthread -lprotobuf -llog4cplus
#$(CC) -o client $(client_objects)  /home/cq/jsoncpp/lib/libjson.a  -lpthread -lprotobuf -llog4cplus

Socket: Socket.cpp
ServerSocket: ServerSocket.cpp
ClientSocket: ClientSocket.cpp 
ServerMain: ServerMain.cpp
ClientMain: ClientMain.cpp ConnectionPool.cpp
ConnectionPool: ConnectionPool.cpp ClientSocket.cpp
sm.SocketMessage.pb.h sm.SocketMessage.pb.cc:sm.SocketMessage.proto
	protoc --cpp_out=$(shell pwd) sm.SocketMessage.proto


clean:
	rm -f *.o server client
	rm -f *.txt
