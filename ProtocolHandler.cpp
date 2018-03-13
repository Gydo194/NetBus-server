/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ProtocolHandler.cpp
 * Author: gydo194
 * 
 * Created on March 7, 2018, 9:22 PM
 */


#include <cstdlib>
#include <cstring>
#include <iostream>

#include "ProtocolHandler.h"

/*
 Protocol V1:
 Byte 1: Mesage Type
 Byte 2: Message source
 Byte 3: Message destination (0 for server?)
 Byte 4-*: Message content
 */


ProtocolHandler::ProtocolHandler() {
    //allocate memory for strings
    typeHeader = (char *) malloc((sizeof (char)) * (MSG_TYPE_HEADER_SIZE + 1));
    messageBody = (char*) malloc((sizeof (char)) * (MSG_BODY_BUFFER_SIZE + 1));
    srcHeader = (char*) malloc((sizeof (char))*(MSG_SRC_HEADER_SIZE + 1));
    destHeader = (char*) malloc((sizeof (char))*(MSG_DEST_HEADER_SIZE + 1));
}

ProtocolHandler::ProtocolHandler(const ProtocolHandler& orig) {
}

ProtocolHandler::~ProtocolHandler() {
    std::cout << "Destroying Protocol Handler...\n";
    free(typeHeader);
    free(messageBody);
    free(srcHeader);
    free(destHeader);
}

void ProtocolHandler::parseMessageType() {
    bzero(typeHeader, MSG_TYPE_HEADER_SIZE);
    strncpy(typeHeader, rawInput + MSG_TYPE_HEADER_START, MSG_TYPE_HEADER_END - MSG_TYPE_HEADER_START);
    //No need to add NULL pointer now, as we initialized the array to NULL bytes using bzero()
    messageType = atoi(typeHeader);
}

void ProtocolHandler::setInput(char* input) {
    ProtocolHandler::rawInput = input;
}

void ProtocolHandler::parseMessageBody() {
    bzero(messageBody, MSG_BODY_BUFFER_SIZE);
    strncpy(messageBody, rawInput + MSG_BODY_START, MSG_BODY_BUFFER_SIZE - MSG_BODY_START);
}

void ProtocolHandler::parseMessageSource() {
    bzero(srcHeader, MSG_SRC_HEADER_SIZE);
    strncpy(srcHeader, rawInput + MSG_SRC_HEADER_START, MSG_SRC_HEADER_END - MSG_SRC_HEADER_START);
    messageSource = atoi(srcHeader);
}

void ProtocolHandler::parseMessageDestination() {
    bzero(destHeader, MSG_DEST_HEADER_SIZE);
    strncpy(destHeader, rawInput + MSG_DEST_HEADER_START, MSG_DEST_HEADER_END - MSG_DEST_HEADER_START);
    messageDestination = atoi(destHeader);
}

uint16_t ProtocolHandler::getMessageType() {
    return messageType;
}

char *ProtocolHandler::getMessageBody() {
    return messageBody;
}

void ProtocolHandler::parseMessage() {
    parseMessageType();
    parseMessageSource();
    parseMessageDestination();
    parseMessageBody();
}

Message ProtocolHandler::getMessage() {
    Message msg;
    msg.setMessageType(messageType);
    msg.setMessageSource(messageSource);
    msg.setMessageDestination(messageDestination);
    msg.setMessageBody(messageBody);
    return msg;
}

void ProtocolHandler::setMessageParams(Message *msg) {
    msg->setMessageType(messageType);
    msg->setMessageSource(messageSource);
    msg->setMessageDestination(messageDestination);
    msg->setMessageBody(messageBody);
}

