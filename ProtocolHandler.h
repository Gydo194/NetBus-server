 /*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ProtocolHandler.h
 * Author: gydo194
 *
 * Created on March 7, 2018, 9:22 PM
 */

#ifndef PROTOCOLHANDLER_H
#define PROTOCOLHANDLER_H

#include "Message.h"


#define MSG_TYPE_HEADER_START 0 //type header start byte
#define MSG_TYPE_HEADER_END 1 //type header end byte, including the null terminator
#define MSG_TYPE_HEADER_SIZE 1 //type header buffer size in bytes (min: total size from start to end)

#define MSG_SRC_HEADER_START 1
#define MSG_SRC_HEADER_END 2
#define MSG_SRC_HEADER_SIZE 1

#define MSG_DEST_HEADER_START 2
#define MSG_DEST_HEADER_END 3
#define MSG_DEST_HEADER_SIZE 1


#define MSG_BODY_BUFFER_SIZE 30 //message body max size
#define MSG_BODY_START 3
#define MSG_BODY_END 30


class ProtocolHandler {
public:
    ProtocolHandler();
    ProtocolHandler(const ProtocolHandler& orig);
    virtual ~ProtocolHandler();
    uint16_t getMessageType();    
    uint16_t getMessageSource();
    uint16_t getMessageDestination();
    char *getMessageBody();
    
    void parseMessage();
    
    void setInput(char *input);
    void getInput();
    
    Message getMessage();
    void setMessageParams(Message *msg);
private:
    char *rawInput;
    uint16_t messageType;
    uint16_t messageSource;
    uint16_t messageDestination;
    char *messageBody;
    char *typeHeader;
    char *srcHeader;
    char *destHeader;
    void parseMessageType();
    void parseMessageSource();
    void parseMessageDestination();
    void parseMessageBody();
    

};

#endif /* PROTOCOLHANDLER_H */

