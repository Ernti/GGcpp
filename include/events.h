#ifndef EVENTS_H
#define EVENTS_H

#include "SDL.h"
#include <iostream>
#include <string>
#include "gamevariables.h"
#include "player.h"

class Events
{
    public:
        Events();
        virtual ~Events();
        void eventLoop();
        SDL_Event event;
        void addPlayer(Player*);
    protected:
    private:
        Player* player;
        bool movecam;
        bool shift;
        bool chatActive;
};

#endif // EVENTS_H
