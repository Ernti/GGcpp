#ifndef PACKET_H
#define PACKET_H

#include <cstring>
#include <string>
#include "SDL_net.h"

class Packet
{
    public:
        Packet();
        virtual ~Packet();
        uint32_t id;
        char chat[16];
        int32_t x;
        int32_t y;
        int32_t targetX;
        int32_t targetY;
    protected:
    private:
};

#endif // PACKET_H
