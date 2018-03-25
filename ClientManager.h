#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H


#include "Client.h"
#include <map>
#include <cstring>

using namespace std;

class ClientManager
{
public:
    ClientManager();
    ~ClientManager();
    static map<string,Client> clients;
    static void registerClient(string id, Client c);
    //static void removeClient

};

#endif // CLIENTMANAGER_H
