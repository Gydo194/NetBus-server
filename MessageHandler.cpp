#include "MessageHandler.h"
#include <map>
#include <iostream>
#include <algorithm>

using namespace std;

map<string,MessageHandler::ActionCallBack> MessageHandler::callbacks;

MessageHandler::MessageHandler()
{
}

MessageHandler::~MessageHandler()
{
}

void MessageHandler::addCallBack(string key, MessageHandler::ActionCallBack cb)
{
    callbacks.insert(pair<string,MessageHandler::ActionCallBack>(key,cb));
}

void MessageHandler::callCallback(string cbId, Message *msg)
{
    /*
    if(callbacks.find(cbId) != callbacks.end()) {
        cout << "CALLBACK EXISTS IN MAP\n";
        callbacks[cbId](msg);
    }
    */
    try {
        callbacks.at(cbId)(msg);
    } catch(out_of_range e) {
        cout << "[MESSAGEHANDLER] [CALLCALLBACK] Caught out of range; requested action does not exist!\n";
    }
}

void MessageHandler::handle(Message *msg)
{
    //check a param for name
    //maybe use exception instead of find() check
    cout << "[MESSAGEHANDLER] MessageHandler::handle() called; calling callback.\n";
    //string
    //callCallback("derp",msg);
    try {
        //callCallback(msg->params.at(MSGHANDLER_ACTION_PARAM_NAME),msg);
        string cbId = msg->params.at(MSGHANDLER_ACTION_PARAM_NAME);
        cout << "[MESSAGEHANDLER] [CALLBACK] Callback name = '" << cbId << "'" << endl;
        callCallback(cbId,msg);
    } catch(out_of_range e) {
        cout << "[MESSAGEHANDLER] [HANDLE] Caught out of range! cannot request action param (is it given?)\n";
    }
}
