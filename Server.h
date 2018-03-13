/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Server.h
 * Author: gydo194
 *
 * Created on March 7, 2018, 9:09 PM
 */

#ifndef SERVER_H
#define SERVER_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> //sockaddr, socklen_t
#include <arpa/inet.h>
#include <netdb.h>
#include <iostream>

#define INPUT_BUFFER_SIZE 100 //test: 100 bytes of buffer
#define DEFAULT_PORT 9034

class Server {
public:
    Server();
    Server(int port);
    Server(const Server& orig);
    virtual ~Server();
    void shutdown();
    void init();
    void run();
    void setNewConnectionCallback(void (*ncc)(uint16_t fd));
    void setReceiveCallBack(void (*rc)(uint16_t fd, char *buffer));
    void setDisconnectCallback(void (*dc)(uint16_t fd));
    void sendTo(uint16_t fd, char *messageBuffer);
private:
    //fd_set file descriptor sets for use with FD_ macros
    fd_set masterfds;
    fd_set tempfds;
    
    //unsigned integer to keep track of maximum fd value, required for select()
    uint16_t maxfd;
    
    //socket file descriptors
    int mastersocket_fd;
    int tempsocket_fd;
    
    //client connection data
    struct sockaddr_storage client_addr;
    //server socket details
    struct sockaddr_in servaddr;
    //input buffer
    char input_buffer[INPUT_BUFFER_SIZE];
    
    char remote_ip[INET6_ADDRSTRLEN];
    int numbytes;
    
    void (*newConnectionCallback) (uint16_t fd);
    void (*receiveCallback) (uint16_t fd, char *buffer);
    void (*disconnectCallback) (uint16_t fd);
    
    
    //function prototypes
    void setup(int port);
    void initializeSocket();
    void bindSocket();
    void startListen();
    void handleNewConnection();
    void recvInputFromExisting(int fd);
    
    //void *getInetAddr(struct sockaddr *saddr);
    

};

#endif /* SERVER_H */

