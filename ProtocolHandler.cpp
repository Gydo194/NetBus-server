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

    //maybe use strpbrk() to get a pointer to the char, then strcpy / append original pointer to new pointer into correct buffer;
    //set original pointer to new pointer + 1 (exclude = / & chars)


    //print every character of string
    for(size_t i = 0; i < strlen(input); i++) {
        //printf("CHAR: '%c'\n",*(input+i));
        processChar(*(input+i));
    }
    append();
    resetState();

}

void ProtocolHandler::processChar(char in)
{
    switch(in) {
    case PH_PAIR_DELIMITER:
        cout << "switching to enum state KEY\n";
        append();
        resetState();
        break;
    case PH_VALUE_DELIMITER:
        cout << "switching to enum state VALUE\n";
        state = VALUE; //read into VALUE buffer from now
        break;
    case '\n':
        //temporary solution to throw out new line characters
        cout << "Skipping newline\n";
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

}

void ProtocolHandler::resetState()
{
    //clear buffers
    keyBuffer.clear();
    valueBuffer.clear();
    state = KEY; //reset back to initial state to read in to key buffer
}
