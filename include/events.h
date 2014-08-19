#ifndef EVENTS_H
#define EVENTS_H

#include "SDL.h"
#include <iostream>
#include "gamevariables.h"
#include "player.h"

class Events
{
    public:
        Events(std::vector<Packet*>*, std::vector<Packet*>*);
        virtual ~Events();
        void eventLoop();
        SDL_Event event;
        void addPlayer(Player*);
    protected:
    private:
        Player* player;
        bool movecam;
        bool shift;
        std::vector<Packet*>* broadcastlist;
        std::vector<Packet*>* receiverlist;
};

#endif // EVENTS_H
