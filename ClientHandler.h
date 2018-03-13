/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ClientHandler.h
 * Author: gydo194
 *
 * Created on March 10, 2018, 8:50 PM
 */

#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#define CLIENT_MAX size_t 10

#include <map>
#include <cstdint>

#include "Client.h"


class ClientHandler {
public:
    ClientHandler();
    ClientHandler(const ClientHandler& orig);
    virtual ~ClientHandler();
    static void setClientFd(int clientNo, int fd);
    static void removeClient(uint16_t fd);
    static uint16_t getClientFd(int clientNo);
private:
    static std::map<int,Client> clients;
    

};

#endif /* CLIENTHANDLER_H */

