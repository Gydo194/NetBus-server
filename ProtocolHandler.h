#ifndef PROTOCOLHANDLER_H
#define PROTOCOLHANDLER_H

#define PH_KEY_LEN 3
#define PH_VAL_LEN 3
#define PH_PAIR_DELIMITER '&'
#define PH_VALUE_DELIMITER '='

class ProtocolHandler
{
public:
    ProtocolHandler();
    ~ProtocolHandler();
    void processInput(char *input);
private:
    void processChar(char in);
};

#endif // PROTOCOLHANDLER_H
