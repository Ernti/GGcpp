#ifndef TEXTURIZER_H
#define TEXTURIZER_H


#include <SDL.h>
#include "SDL_image.h"
#include <iostream>
#include <vector>

class Texturizer
{
    public:
        Texturizer(SDL_Renderer*);
        virtual ~Texturizer();
        SDL_Texture* loadTexture(int);
    protected:
    private:
        std::vector<SDL_Texture*> tex;
};

#endif // TEXTURIZER_H
