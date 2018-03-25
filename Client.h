#ifndef CLIENT_H
#define CLIENT_H

#include <cstdint>

class Client
{
public:
    Client();
    ~Client();
    uint16_t fd;

};

#endif // CLIENT_H
