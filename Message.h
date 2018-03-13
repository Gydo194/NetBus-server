/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Message.h
 * Author: gydo194
 *
 * Created on March 8, 2018, 7:38 AM
 */

#ifndef MESSAGE_H
#define MESSAGE_H
#define MESSAGE_BODY_SIZE 100


#include <cstdint>


class Message
{
public:
    Message();
    Message(const Message& orig);
    virtual ~Message();

    //message header data members
    uint16_t messageType = 0;
    uint16_t messageSource = 0;
    uint16_t messageDestination = 0;
    //message body
    char *messageBody;



    void setMessageType(int type);
    void setMessageBody(char *body);
    uint16_t getMessageType();
    char *getMessageBody();

    //TODO: either remove getter/setter functions or move to cpp
    uint16_t getMessageDestination() const {
        return messageDestination;
    }

    void setMessageDestination(uint16_t messageDestination) {
        this->messageDestination = messageDestination;
    }

    uint16_t getMessageSource() const {
        return messageSource;
    }

    void setMessageSource(uint16_t messageSource) {
        this->messageSource = messageSource;
    }

    uint16_t getMessageType() const {
        return messageType;
    }

    void setMessageType(uint16_t messageType) {
        this->messageType = messageType;
    }


    void printDetails();



private:


};

#endif /* MESSAGE_H */
