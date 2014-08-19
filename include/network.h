#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <SDL.h>
#include <SDL_net.h>
#include <cstring>
#include <chrono>
#include <thread>
#include <vector>
#include "GameVariables.h"

using namespace std;

#include "packet.h"

class Network
{
    public:
        Network(Packet*);
        virtual ~Network();

        void sender();
        void receiver();

        thread receiverthread;
        thread senderthread;
        bool running;

        std::vector<Packet*> broadcastlist;
        std::vector<Packet*> receivelist;

        void loop();
    protected:
    private:
        SDLNet_SocketSet sockets;
        TCPsocket socket;
};

#endif // NETWORK_H
