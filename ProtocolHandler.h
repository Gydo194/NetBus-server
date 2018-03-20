#ifndef PROTOCOLHANDLER_H
#define PROTOCOLHANDLER_H

#define PH_KEY_LEN 3
#define PH_VAL_LEN 3
#define PH_PAIR_DELIMITER '&'
#define PH_VALUE_DELIMITER '='

#include <cstring>
#include <iostream>
#include <map>

using namespace std;

class ProtocolHandler
{
public:
    ProtocolHandler();
    ~ProtocolHandler();
    void processInput(char *input);
    map<string,string> values;
private:
    void processChar(char in);
    void processNewChar(char in);
    void append();
    void resetState();
    string keyBuffer;
    string valueBuffer;
    enum states { KEY,VALUE } state;
};

#endif // PROTOCOLHANDLER_H
