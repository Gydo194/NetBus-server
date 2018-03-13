/*
 * File:   main.cpp
 * Author: gydo194
 *
 * Created on March 7, 2018, 9:08 PM
 */

#include "Server.h"
#include "Message.h"
#include "ProtocolHandler.h"
#include "ClientHandler.h"
#include "MessageHandler.h"
#include "ServerCallbackHandlerService.h"
#include "Commons.h" //global extern variables
#include "SignalHandlers.h"

#include <iostream>
#include <csignal>

using namespace std;

Server s; //forward declaration of Server s from Commons.h
int main(int argc, char** argv)
{
    cout << "[NETBUS] [BOOTSTRAP] Starting bootstrap" << endl;
    cout << "[NETBUS] [BOOTSTRAP] Binding Interrupt signal handlers..." << endl;
    signal(SIGINT,globalSignalHandler);
    signal(SIGABRT,globalSignalHandler);
    signal(SIGQUIT,globalSignalHandler);
    cout << "[NETBUS] [BOOTSTRAP] Binding Server API callback function pointers..." << endl;
    s.setNewConnectionCallback(&ServerCallbackHandlerService::processNewConnection);
    s.setReceiveCallBack(&ServerCallbackHandlerService::processNewInput);
    s.setDisconnectCallback(&ServerCallbackHandlerService::processDisconnect);
    cout << "[NETBUS] [BOOTSTRAP] Initializing Sockets..." << endl;
    s.init();
    cout << "[NETBUS] [BOOTSTRAP] Starting Server..." << endl;
    s.run();

    //will never get past this point
    cout << "[NETBUS] [ERROR] Illegal State detected (End of Main)" << endl;
    return 0;
}
