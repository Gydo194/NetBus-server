/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Message.cpp
 * Author: gydo194
 * 
 * Created on March 8, 2018, 7:38 AM
 */

#include <cstdlib>
#include <cstring>
#include <iostream>

#include "Message.h"



Message::Message() {
}

Message::Message(const Message& orig) {
}

Message::~Message() {
}

void Message::setMessageType(int type) {
    messageType = type;
}

uint16_t Message::getMessageType() {
    return messageType;
}

void Message::setMessageBody(char *body) {
    messageBody = body;
}

char *Message::getMessageBody() {
    return messageBody;
}
 

void Message::printDetails() {
    printf("Message of type '%hu' from '%hu' to '%hu' with content '%s'.\n",messageType,messageSource, messageDestination, messageBody);
}