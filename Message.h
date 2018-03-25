#ifndef MESSAGE_H
#define MESSAGE_H


#include <map>
#include <cstring>
#include <cstdint>

using namespace std;

class Message
{
public:
    Message();
    Message(map<string,string> values);
    ~Message();
    map<string,string> params;
private:
    
};

#endif // MESSAGE_H
