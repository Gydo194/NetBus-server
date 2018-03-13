/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ServerCallbackHandlerService.cpp
 * Author: gydo194
 * 
 * Created on March 11, 2018, 3:57 PM
 */
#include <iostream>
#include "ServerCallbackHandlerService.h"
#include "MessageHandler.h"
#include "ClientHandler.h"

ProtocolHandler ServerCallbackHandlerService::ph;

ServerCallbackHandlerService::ServerCallbackHandlerService() {
}

ServerCallbackHandlerService::ServerCallbackHandlerService(const ServerCallbackHandlerService& orig) {
}

ServerCallbackHandlerService::~ServerCallbackHandlerService() {
}

void ServerCallbackHandlerService::processNewConnection(uint16_t fd) {
    std::cout << "[SERVERCALLBACKHANDLERSERVICE] ServerCallbackHandlerService::processNewConnection called.\n";
}

void ServerCallbackHandlerService::processDisconnect(uint16_t fd) {
    std::cout << "[SERVERCALLBACKHANDLERSERVICE] ServerCallbackHandlerService::processDisconnect() called w/fd " << fd << ".\n";
    //remove fd from clients
}

void ServerCallbackHandlerService::processNewInput(uint16_t fd, char* buffer) {
    std::cout << "[SERVERCALLBACKHANDLERSERVICE] ServerCallbackHandllerService::processNewInput() called\n";
    printf("[SERVERCALLBACKHANDLERSERVICE] ServerCallbackHandlerService::processNewInput(): fd = '%hu' raw input = '%s'.\n", fd, buffer);
    ph.setInput(buffer);
    ph.parseMessage();
    Message msg;
    ph.setMessageParams(&msg);
    MessageHandler::handle(&msg, fd); //send the processing on to the message handler
}
