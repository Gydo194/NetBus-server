#include "Message.h"
#include "MessageHandler.h"
#include "Server.h"

#include <iostream>
#include <map>
#include "ClientManager.h"

using namespace std;

namespace Actions
{
    
    

void testAction(Message *msg)
{
    cout << "TEST ACTION CALLED\n";
}

void dumpMessageParams(Message *msg)
{
    cout << "[DUMPMESSAGE] Dumping message contents\n";
    cout << "[DUMPMESSAGE] Message source fd.\n";
    map<string,string>::iterator paramIterator;
    for(paramIterator = msg->params.begin(); paramIterator != msg->params.end(); paramIterator++) {
        cout << "[DUMPMESSAGE] Message param key: '" << paramIterator->first << "' value '" << paramIterator->second << "'.\n";
    }
}


void registerClient(Message *msg) {
    Client c;
    ClientManager::registerClient("client",c);
}


}
