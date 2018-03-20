#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <map>
#include "Message.h"

#define MSGHANDLER_ACTION_PARAM_NAME "test"

using namespace std;



class MessageHandler
{
public:
    MessageHandler();
    ~MessageHandler();
    typedef void (*ActionCallBack)(Message *msg);
    static void handle(Message *msg);
    static void addCallBack(string key, ActionCallBack cb);
private:
    static map<string,ActionCallBack> callbacks;
    static void callCallback(string cbId, Message *msg);
};

#endif // MESSAGEHANDLER_H
