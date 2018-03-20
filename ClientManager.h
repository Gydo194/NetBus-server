#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <map>
#include <cstring>

using namespace std;

class ClientManager
{
public:
    ClientManager();
    ~ClientManager();
    map<string,uint16_t> clients;

};

#endif // CLIENTMANAGER_H
