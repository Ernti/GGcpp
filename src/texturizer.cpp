#include "texturizer.h"

Texturizer::Texturizer(SDL_Renderer* screen)
{
    SDL_Surface* surf;
    surf = IMG_Load( "gfx/spaceship.png");
    if( surf == NULL ) {
            std::cout << " could not load image!" << std::endl;
    }
    tex.push_back(SDL_CreateTextureFromSurface(screen, surf));
    SDL_FreeSurface(surf);
}

Texturizer::~Texturizer()
{
    for(unsigned int i = 0; i < tex.size(); i++)
    {
        SDL_DestroyTexture(tex[i]);
    }
}

SDL_Texture* Texturizer::loadTexture(int id)
{
    return tex[id];
}
