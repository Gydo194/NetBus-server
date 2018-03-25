#include "ClientManager.h"
#include <cstring>
#include <cstdint>
#include <map>
#include <cstring>
#include <cstdint>
#include <iostream>

using namespace std;

map<string,Client> ClientManager::clients; //forward declaration of static map

ClientManager::ClientManager()
{
}

ClientManager::~ClientManager()
{
}

void ClientManager::registerClient(string cid, Client c) {
    cout << "[CLIENT MANAGER] Registering client with name '" << cid << "' with FD '" << c.fd << "'.!\n";
    clients.insert(pair<string,Client>(cid,c));
}

