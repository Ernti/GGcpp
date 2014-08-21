#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <SDL.h>
#include <SDL_net.h>
#include <cstring>
#include <chrono>
#include <thread>
#include <vector>
#include "gamevariables.h"
#include "player.h"
#include "movement.h"
#include "renderer.h"
#include "packet.h"

using namespace std;

class Network
{
    public:
        Network(Packet*);
        virtual ~Network();

        void start(Movement*, Renderer*, Player*);



        void loop();
    protected:
    private:
        Movement* movement;
        Renderer* renderer;
        Player* player;

        SDLNet_SocketSet sockets;
        TCPsocket socket;

        void sender();
        void receiver();

        thread receiverthread;
        thread senderthread;
        bool running;
        Uint32 lasttick;
        Uint32 nowtick;

        std::vector<Packet*> broadcastlist;
        std::vector<Packet*> receivelist;

        std::vector<Spaceship*> spaceschips;

        unsigned int id;
};

#endif // NETWORK_H
