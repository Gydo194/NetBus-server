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
#include "ServerAPIHandler.h"
#include "ProtocolHandler.h"
#include "Message.h"
#include "MessageHandler.h"
#include "Commons.h"

ProtocolHandler ph;
ServerAPIHandler::ServerAPIHandler() {
}

ServerAPIHandler::ServerAPIHandler(const ServerAPIHandler& orig) {
}

ServerAPIHandler::~ServerAPIHandler() {
}

void ServerAPIHandler::processNewConnection(uint16_t fd) {
    std::cout << "[SERVERCALLBACKHANDLERSERVICE] ServerCallbackHandlerService::processNewConnection called.\n";
}

void ServerAPIHandler::processDisconnect(uint16_t fd) {
    std::cout << "[SERVERCALLBACKHANDLERSERVICE] ServerCallbackHandlerService::processDisconnect() called w/fd " << fd << ".\n";
    //remove fd from clients
}



void ServerAPIHandler::processNewInput(uint16_t fd, char* buffer) {
    std::cout << "[SERVERCALLBACKHANDLERSERVICE] ServerCallbackHandllerService::processNewInput() called\n";
    printf("[SERVERCALLBACKHANDLERSERVICE] ServerCallbackHandlerService::processNewInput(): fd = '%hu' raw input = '%s'.\n", fd, buffer);
    ph.processInput(buffer); //process received input
    Message msg; //build a Message object for processing
    msg.params = ph.values; //set it's parameter map to the processed input value map
    ph.values.clear(); //reset value map
    msg.connector.source_fd = fd;
    MessageHandler::handle(&msg); //call Message Handler to handle the message based on stored params in map
}
