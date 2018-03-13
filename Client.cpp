/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Client.cpp
 * Author: gydo194
 * 
 * Created on March 11, 2018, 6:30 AM
 */

#include "Client.h"

Client::Client() {
}

Client::Client(const Client& orig) {
}

Client::~Client() {
}

uint16_t Client::getfd() {
    return fd;
}

void Client::setfd(uint16_t nfd) {
    fd = nfd;
}
