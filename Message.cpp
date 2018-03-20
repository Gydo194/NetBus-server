#include "Message.h"

Message::Message()
{
}

Message::Message(map<string,string> values) {
    params = values;
}

Message::~Message()
{
    
}

