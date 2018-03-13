/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ClientHandler.cpp
 * Author: gydo194
 * 
 * Created on March 10, 2018, 8:50 PM
 */

#include <stdexcept>
#include <iostream>

#include "ClientHandler.h"

std::map<int,Client> ClientHandler::clients;

ClientHandler::ClientHandler() {
}

ClientHandler::ClientHandler(const ClientHandler& orig) {
}

ClientHandler::~ClientHandler() {
}


uint16_t ClientHandler::getClientFd(int clientNo)  {
    //return clients[clientNo];
    //return clients.at(clientNo);
    int ret = 0;
    try {
        ret = clients.at(clientNo).getfd();
    } catch(std::out_of_range e) {
        std::cout << "ClientHandler::getClientFd(): CAUGHT std::out_of_range :" << e.what() << std::endl;
        return 0;
    }
}

void ClientHandler::setClientFd(int clientNo, int fd) {
    printf("ClientHandler::setClientFd(): setting client at #'%d' to '%d'.\n",clientNo,fd);
    clients[clientNo].setfd(fd);
}

void ClientHandler::removeClient(uint16_t clientNo) {
    printf("[CLIENTHANDLER] [REMOVE] Removing client '%hu'.\n",clientNo);
    try {
        clients.at(clientNo).setfd(0);
    } catch(std::out_of_range e) {
        std::cout << "ClientHandler::removeClient() caught std::out_of_range\n";
        std::cout << e.what();
    }
}


