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


ProtocolHandler::ProtocolHandler()
{
    //allocate memory for strings
    //typeHeader = (char *) malloc((sizeof (char)) * (MSG_TYPE_HEADER_SIZE + 1));
    messageBody = (char*) malloc((sizeof (char)) * (MSG_BODY_BUFFER_SIZE + 1));
    //srcHeader = (char*) malloc((sizeof (char))*(MSG_SRC_HEADER_SIZE + 1));
    //destHeader = (char*) malloc((sizeof (char))*(MSG_DEST_HEADER_SIZE + 1));
    tempBuffer = (char*) malloc(sizeof(char)*PROTOCOLHANDLER_TEMPBUFFER_SIZE);
}

ProtocolHandler::ProtocolHandler(const ProtocolHandler& orig)
{
}

ProtocolHandler::~ProtocolHandler()
{
    std::cout << "Destroying Protocol Handler...\n";
    //free(typeHeader);
    free(messageBody);
    //free(srcHeader);
    //free(destHeader);
    free(tempBuffer);
}

void ProtocolHandler::parseMessageType()
{
    bzero(tempBuffer, MSG_TYPE_HEADER_SIZE);
    strncpy(tempBuffer, rawInput + MSG_TYPE_HEADER_START, MSG_TYPE_HEADER_END - MSG_TYPE_HEADER_START);
    //No need to add NULL pointer now, as we initialized the array to NULL bytes using bzero()
    messageType = atoi(tempBuffer);
}

void ProtocolHandler::setInput(char* input)
{
    ProtocolHandler::rawInput = input;
}

void ProtocolHandler::parseMessageBody()
{
    bzero(messageBody, MSG_BODY_BUFFER_SIZE);
    strncpy(messageBody, rawInput + MSG_BODY_START, MSG_BODY_BUFFER_SIZE - MSG_BODY_START);
}

void ProtocolHandler::parseMessageSource()
{
    bzero(tempBuffer, MSG_SRC_HEADER_SIZE);
    strncpy(tempBuffer, rawInput + MSG_SRC_HEADER_START, MSG_SRC_HEADER_END - MSG_SRC_HEADER_START);
    messageSource = atoi(tempBuffer);
}

void ProtocolHandler::parseMessageDestination()
{
    bzero(tempBuffer, MSG_DEST_HEADER_SIZE);
    strncpy(tempBuffer, rawInput + MSG_DEST_HEADER_START, MSG_DEST_HEADER_END - MSG_DEST_HEADER_START);
    messageDestination = atoi(tempBuffer);
}

uint16_t ProtocolHandler::getMessageType()
{
    return messageType;
}

char *ProtocolHandler::getMessageBody()
{
    return messageBody;
}

void ProtocolHandler::parseMessage()
{
    parseMessageType();
    parseMessageSource();
    parseMessageDestination();
    parseMessageBody();
}

Message ProtocolHandler::getMessage()
{
    Message msg;
    msg.setMessageType(messageType);
    msg.setMessageSource(messageSource);
    msg.setMessageDestination(messageDestination);
    msg.setMessageBody(messageBody);
    return msg;
}

void ProtocolHandler::setMessageParams(Message *msg)
{
    msg->setMessageType(messageType);
    msg->setMessageSource(messageSource);
    msg->setMessageDestination(messageDestination);
    msg->setMessageBody(messageBody);
}

char *ProtocolHandler::getHeadersForMessage(Message *msg)
{
    char *tempHeader = (char*) malloc(sizeof(char)*MSG_HEADER_SIZE);
    bzero(tempHeader,sizeof(char)*MSG_HEADER_SIZE);
    sprintf((tempHeader + MSG_TYPE_HEADER_START),"%d",msg->messageType);
    sprintf((tempHeader + MSG_SRC_HEADER_START),"%d",msg->messageSource);
    sprintf((tempHeader + MSG_DEST_HEADER_START),"%d",msg->messageDestination);
    return tempHeader;
}
