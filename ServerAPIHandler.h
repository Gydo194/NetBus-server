/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ServerCallbackHandlerService.h
 * Author: gydo194
 *
 * Created on March 11, 2018, 3:57 PM
 */

#ifndef SERVERCALLBACKHANDLERSERVICE_H
#define SERVERCALLBACKHANDLERSERVICE_H

#include <cstdint>

class ServerAPIHandler {
    
public:
    ServerAPIHandler();
    ServerAPIHandler(const ServerAPIHandler& orig);
    virtual ~ServerAPIHandler();
    static void processNewConnection(uint16_t fd);
    static void processNewInput(uint16_t fd, char *buffer);
    static void processDisconnect(uint16_t fd);
    static void sendMessage(Message *msg);
private:



};

#endif /* SERVERCALLBACKHANDLERSERVICE_H */

