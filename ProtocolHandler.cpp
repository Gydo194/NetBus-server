#include "ProtocolHandler.h"
#include <iostream>
#include <cstring>

using namespace std;

ProtocolHandler::ProtocolHandler()
{
    keyBuffer = string();
    valueBuffer = string();
}

ProtocolHandler::~ProtocolHandler()
{
}

void ProtocolHandler::processInput(char *input)
{
    cout << "[PROTOCOLHANDLER] processInput called\n";




    
    //print every character of string
    for(size_t i = 0; i < strlen(input); i++) {
        //printf("CHAR: '%c'\n",*(input+i));
        processChar(*(input+i));
    }
    append();
    
}

void ProtocolHandler::processChar(char in)
{
   //cout << "running char handler\n";
    switch(in) {
    case '&':
        state = KEY; //reset to reading into KEY buffer
        append();
        break;
    case '=':
        state = VALUE; //read into VALUE buffer from now
        break;
    default:
        processNewChar(in); //read input char into correct buffer
        break;
    }
}

void ProtocolHandler::processNewChar(char in)
{
    switch(state) {
    case KEY:
        cout << "appending '" << in << "' to KEY buffer\n";
        //keyBuffer.append(in,1);
        keyBuffer += in;
        break;
    case VALUE:
        cout << "appending '" << in << "' to VALUE buffer\n";
        //valueBuffer.append(in,1);
        valueBuffer += in;
        break;

    }
}

void ProtocolHandler::append()
{
    cout << "STORING '" << keyBuffer << "' w/val '" << valueBuffer << "'.\n";
    //store data
    values.insert(std::pair<string,string>(keyBuffer,valueBuffer));
    //clear buffers
    keyBuffer.clear();
    valueBuffer.clear();
}
