/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Client.h
 * Author: gydo194
 *
 * Created on March 11, 2018, 6:30 AM
 */

#ifndef CLIENT_H
#define CLIENT_H

#include <cstdint>


class Client {
public:
    Client();
    Client(const Client& orig);
    virtual ~Client();
    uint16_t getfd();
    void setfd(uint16_t nfd);
private:
    uint16_t fd;
    

};

#endif /* CLIENT_H */

