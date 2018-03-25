/*
 * File:   main.cpp
 * Author: gydo194
 *
 * Created on March 7, 2018, 9:08 PM
 */

#include "Server.h"
#include "ServerAPIHandler.h"
#include "Commons.h" //global extern variables
#include "SignalHandlers.h"
#include "MessageHandler.h"
#include "Actions.h"

#include <iostream>
#include <csignal>

using namespace std;
using namespace Actions;

Server s; //forward declaration of Server s from Commons.h
int main(int argc, char** argv)
{
    cout << "[NETBUS] [BOOTSTRAP] Starting bootstrap" << endl;
    cout << "[NETBUS] [BOOTSTRAP] Binding Interrupt signal handlers..." << endl;
    signal(SIGINT,globalSignalHandler);
    signal(SIGABRT,globalSignalHandler);
    signal(SIGQUIT,globalSignalHandler);


    cout << "[NETBUS] [BOOTSTRAP] Binding Server callback function pointers..." << endl;
    s.setNewConnectionCallback(&ServerAPIHandler::processNewConnection);
    s.setReceiveCallBack(&ServerAPIHandler::processNewInput);
    s.setDisconnectCallback(&ServerAPIHandler::processDisconnect);

    cout << "[NETBUS] [BOOTSTRAP] Binding Action callbacks...\n";
    MessageHandler::addCallBack("test",(MessageHandler::ActionCallBack) &testAction);
    MessageHandler::addCallBack("dump",(MessageHandler::ActionCallBack) &dumpMessageParams);
    MessageHandler::addCallBack("register",(MessageHandler::ActionCallBack) &registerClient);


    cout << "[NETBUS] [BOOTSTRAP] Initializing Sockets..." << endl;
    s.init();
    cout << "[NETBUS] [BOOTSTRAP] Starting Server..." << endl;
    s.run();

    //should never get past this point
    cout << "[NETBUS] [ERROR] Illegal State detected (End of Main)" << endl;
    return 0;
}
