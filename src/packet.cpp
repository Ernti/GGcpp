#include "packet.h"

Packet::Packet()
{
    std::string tmp = "";
    strncpy(chat, tmp.c_str(), sizeof(chat));
}

Packet::~Packet()
{
    //dtor
}
