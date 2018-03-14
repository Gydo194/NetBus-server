/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Server.cpp
 * Author: gydo194
 * 
 * Created on March 7, 2018, 9:09 PM
 */

#include "Server.h"

Server::Server() {
    setup(DEFAULT_PORT);
}

Server::Server(int port) {
    setup(port);
}

Server::Server(const Server& orig) {
}

Server::~Server() {
    std::cout << "[SERVER] [DESTRUCTOR] Destroying Server...\n";
    close(mastersocket_fd);
}

void Server::setup(int port) {
    //std::cout << "[SERVER] [BOOTSTRAP] starting server..." << std::endl;

    mastersocket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (mastersocket_fd < 0) {
        perror("Socket creation failed");
    }

    FD_ZERO(&masterfds);
    FD_ZERO(&tempfds);

    memset(&servaddr, 0, sizeof (servaddr)); //bzero
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(port);


    //printf("[SERVER] [DEBUG] main fd '%d'\n", mastersocket_fd);

}

void Server::initializeSocket() {
    std::cout << "[SERVER] initializing socket\n";
    int opt_value = 1;
    int ret_test = setsockopt(mastersocket_fd, SOL_SOCKET, SO_REUSEADDR, (char *) &opt_value, sizeof (int));
    printf("[SERVER] setsockopt() ret %d\n", ret_test);
    if (ret_test < 0) {
        perror("]SERVER] [ERROR] setsockopt() failed");
    }
}

void Server::bindSocket() {
    std::cout << "[SERVER] binding...\n";
    int bind_ret = bind(mastersocket_fd, (struct sockaddr*) &servaddr, sizeof (servaddr));
    printf("[SERVER] bind() ret %d\n", bind_ret);
    if (bind_ret < 0) {
        perror("[SERVER] bind() failed");
    }
    FD_SET(mastersocket_fd, &masterfds);
    maxfd = mastersocket_fd;
}

void Server::startListen() {
    std::cout << "[SERVER] listen starting...\n";
    int listen_ret = listen(mastersocket_fd, 3);
    printf("[SERVER] listen() ret %d\n", listen_ret);
    if (listen_ret < 0) {
        perror("[SERVER] [ERROR] listen() failed");
    }

}

void Server::shutdown() {
    printf("[SERVER] [DEBUG] [SHUTDOWN] closing master fd..  ret '%d'.\n", close(mastersocket_fd));
}

void Server::handleNewConnection() {
    std::cout << "[SERVER] [CONNECTION] handling new connection\n";
    socklen_t addrlen = sizeof (client_addr);
    tempsocket_fd = accept(mastersocket_fd, (struct sockaddr*) &client_addr, &addrlen);
    if (tempsocket_fd < 0) {
        perror("[SERVER] [ERROR] accept() failed");
    } else {
        FD_SET(tempsocket_fd, &masterfds);
        if (tempsocket_fd > maxfd) {
            maxfd = tempsocket_fd;
            std::cout << "[SERVER] incrementing maxfd to " << maxfd << std::endl;
        }
        //printf("[SERVER] [CONNECTION] New connection from '%s' on socket fd '%d'.\n", inet_ntop(client_addr.ss_family, getInetAddr((struct sockaddr*) &client_addr), remote_ip, INET6_ADDRSTRLEN), tempsocket_fd); //from src ip
        printf("[SERVER] [CONNECTION] New connection on socket fd '%d'.\n",tempsocket_fd);
    }
    newConnectionCallback(tempsocket_fd);
}

void Server::recvInputFromExisting(int fd) {
    std::cout << "[SERVER] [RECV] receiving from existing...\n";
    int nbytesrecv = recv(fd, input_buffer, INPUT_BUFFER_SIZE, 0);
    if (nbytesrecv <= 0) {
        //problem
        if (0 == nbytesrecv) {
            //printf("[SERVER] [CONNECTION] client '%s' on socket fd '%d' closed connection.\n", inet_ntop(client_addr.ss_family, getInetAddr((struct sockaddr*) &client_addr), remote_ip, INET6_ADDRSTRLEN), fd); //from src ip
            printf("[SERVER] [CONNECTION] client at fd '%d' closed connection.\n",fd);
            disconnectCallback((uint16_t)fd);
        } else {
            perror("[SERVER] [ERROR] recv() failed");
        }
        close(fd); //well then, bye bye.
        FD_CLR(fd, &masterfds);
        return;
    }
    //add NULL terminator
    printf("[SERVER] [RECV] Received '%s' from client!\n", input_buffer);
    //call handler function
    receiveCallback(fd,input_buffer);
    memset(&input_buffer, 0, INPUT_BUFFER_SIZE); //zero buffer
}

void Server::run() {
    int sel = 0;
    while (true) {
        std::cout << "[SERVER] [MISC] starting server main loop\n";
        tempfds = masterfds; //select is destructive on the fd_set, so make a copy

        printf("[SERVER] [MISC] max fd = '%hu' \n", maxfd);
        std::cout << "[SERVER] [MISC] calling select()\n";
        sel = select(maxfd + 1, &tempfds, NULL, NULL, NULL); //blocks until activity
        printf("[SERVER] [MISC] select() ret %d, processing...\n", sel);
        if (sel < 0) {
            perror("[SERVER] [ERROR] S elect() failed");
            shutdown();
        }

        //no problems, we're all set

        //loop the fd_set and check which socket has interactions available
        for (int i = 0; i <= maxfd; i++) {
            if (FD_ISSET(i, &tempfds)) {
                if (mastersocket_fd == i) {
                    //new connection on master socket
                    handleNewConnection();
                } else {
                    //exisiting connection has new data
                    recvInputFromExisting(i);
                }
            }
        }


    }
}

void Server::init() {
    initializeSocket();
    bindSocket();
    startListen();
}

void Server::setReceiveCallBack(void (*rc)(uint16_t fd, char *buffer)) {
     receiveCallback = rc;
}

void Server::setNewConnectionCallback(void(*ncc)(uint16_t)) {
    newConnectionCallback = ncc;
}

void Server::setDisconnectCallback(void(*dc)(uint16_t)) {
    disconnectCallback = dc;
}



void Server::sendTo(uint16_t fd, void* messageBuffer) {
    int nbsent = send(fd,messageBuffer,sizeof(messageBuffer),0);
    std::cout << "[SERVER] [SEND] Sent " << nbsent << " bytes to client with fd " << fd << "." << std::endl;
    //delete(&nbsent);
    //printf("[SERVER] [SEND-UNSTABLE] Server::sendTo(): sent '%d' bytes to client fd '%hu'.\n",send(fd,messageBuffer,strlen(messageBuffer),0),fd);
}

