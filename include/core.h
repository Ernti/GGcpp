#ifndef CORE_H
#define CORE_H

#include <SDL.h>
#include "SDL_image.h"
#include <SDL_net.h>
#include "SDL_ttf.h"
#include <cstring>

#include "gamevariables.h"
#include "events.h"
#include "renderer.h"
#include "player.h"
#include "movement.h"
#include "network.h"

class Core
{
    public:
        Core();
        virtual ~Core();
        void loop();
    protected:
    private:
        Events* events;
        Renderer* renderer;
        Player* player;
        Movement* movement;
        Network* network;
};

#endif // CORE_H
