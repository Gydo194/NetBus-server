/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MessageHandler.h
 * Author: gydo194
 *
 * Created on March 10, 2018, 7:02 PM
 */

#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include "Message.h"


class MessageHandler {
public:
    MessageHandler();
    MessageHandler(const MessageHandler& orig);
    virtual ~MessageHandler();
    static void handle(Message *msg, uint16_t fd);
private:

};

#endif /* MESSAGEHANDLER_H */

