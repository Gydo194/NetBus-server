/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MessageHandler.cpp
 * Author: gydo194
 * 
 * Created on March 10, 2018, 7:02 PM
 */

#include <iostream>

#include "MessageHandler.h"
#include "ClientHandler.h"
#include "ProtocolHandler.h"
#include "Server.h"

extern Server s; //forward declaration of extern Server s from Globals.h


MessageHandler::MessageHandler() {
}

MessageHandler::MessageHandler(const MessageHandler& orig) {
}

MessageHandler::~MessageHandler() {
}

void MessageHandler::handle(Message *msg, uint16_t fd) {
    //handle message based on its type; types and defenitions are subject to change.
    printf("[MESSAGEHANDLER] [DEBUG] fd: '%hu'.\n",fd);
    std::cout << "[MESSAGEHANDLER] [DEBUG] MessageHandler::handle(): Dumping incoming message\n";
    msg->printDetails();
    
    uint16_t cfd;
    switch (msg->getMessageType()) {
        case 0:
            //type 0: HELLO
            std::cout << "[MESSAGEHANDLER] MessageHandler::handle(): got message type 0 (HELLO)\n";
            ClientHandler::setClientFd(msg->getMessageSource(), fd);
            break;
        case 1:
            //type 1: BYE
            std::cout << "[MESSAGEHANDLER] MessageHandler::handle(): got message type 1 (BYE)\n";
            cfd = ClientHandler::getClientFd(msg->getMessageSource());
            printf("[MESSAGEHANDLER] MessageHandler: resolved client src '%hu' to fd '%hu' for remove.\n",msg->getMessageSource(),cfd);
            ClientHandler::removeClient(msg->getMessageSource());
            break;
        case 2:
            //type 2: SEND
            std::cout << "[MESSAGEHANDLER] MessageHandler::handle(): got message type 2 (SEND)\n";
            printf("[MESSAGEHANDLER] MessageHandler::handle(): resolved fd for client '%hu' = '%hu'.\n",msg->getMessageDestination(),ClientHandler::getClientFd(msg->getMessageDestination()));
            
            s.sendTo(ClientHandler::getClientFd(msg->getMessageDestination()),ProtocolHandler::getHeadersForMessage(msg)); //send headers WARN: free?
            s.sendTo(ClientHandler::getClientFd(msg->getMessageDestination()),msg->messageBody); //send message body
            break;
        case 3:
            std::cout << "[MESSAGEHANDLER] MessageHandler::handle(): got message type 3 (SERVCMD)\n";
            exit(EXIT_SUCCESS);
            break;
        case 4:
            //reserved message type for unit tests
            std::cout << "[MESSAGEHANDLER] MessageHandler::handle(): got message type 4 (DBG)\n";
            break;
        default:
            std::cout << "[MESSAGEHANDLER] MessageHandler::handle(): got unknown message type " << msg->getMessageType() << " .\n";
            break;
    }
}

