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
private:
    void processChar(char in);
    void processNewChar(char in);
    void append();
    string keyBuffer;
    string valueBuffer;
    map<string,string> values;
    enum states { KEY,VALUE } state;
};

#endif // PROTOCOLHANDLER_H
