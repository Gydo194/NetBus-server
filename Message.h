#ifndef MESSAGE_H
#define MESSAGE_H


#include <map>
#include <cstring>
#include <cstdint>
#include "Server.h"

using namespace std;

class Message
{
public:
    Message();
    Message(map<string,string> values);
    ~Message();
    map<string,string> params;
    Server::Connector connector;
private:
    
};

#endif // MESSAGE_H
