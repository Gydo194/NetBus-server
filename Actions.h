#include "Message.h"
#include "MessageHandler.h"
#include "Server.h"

#include <iostream>
#include <map>

using namespace std;


void testAction(Message *msg)
{
    cout << "TEST ACTION CALLED\n";
}

void dumpMessageParams(Message *msg) {
    cout << "[DUMPMESSAGE] Dumping message contents\n";
    map<string,string>::iterator paramIterator;
    for(paramIterator = msg->params.begin(); paramIterator != msg->params.end(); paramIterator++) {
        cout << "Message param key: '" << paramIterator->first << "' value '" << paramIterator->second << "'.\n";
    }
}