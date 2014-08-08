#ifndef EVENTS_H
#define EVENTS_H

#include "SDL.h"
#include "GameVariables.h"
#include <iostream>

class Events
{
    public:
        Events();
        virtual ~Events();
        void eventLoop();
        SDL_Event event;
    protected:
    private:
};

#endif // EVENTS_H
