#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include "SDL_image.h"
#include <vector>
#include "player.h"
#include "gamevariables.h"
#include "renderable.h"
#include "texturizer.h"

class Renderer
{
    public:
        Renderer();
        virtual ~Renderer();
        void render();
        void addPlayer(Player*);
    protected:
    private:
        SDL_Window* window;
        SDL_Renderer* screen;
        Texturizer* texturizer;
        int screenShiftX;
        int screenShiftY;
        Player* player;
        std::vector<Renderable*> renderlist;
};

#endif // RENDERER_H
