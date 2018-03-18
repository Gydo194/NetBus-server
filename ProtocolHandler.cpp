#include "ProtocolHandler.h"
#include <iostream>
#include <cstring>

using namespace std;

ProtocolHandler::ProtocolHandler()
{
}

ProtocolHandler::~ProtocolHandler()
{
}

void ProtocolHandler::processInput(char *input) {
    cout << "[PROTOCOLHANDLER] processInput called\n";
    for(size_t i = 0; i < strlen(input); i++) {
        printf("CHAR: '%c'\n",*(input+i));
        
    }
}

void ProtocolHandler::processChar(char in) {
    
}