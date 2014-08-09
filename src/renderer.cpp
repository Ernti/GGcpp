#include "renderer.h"

Renderer::Renderer()
{
    window = SDL_CreateWindow("Project Seven", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GameVariables::screenResX, GameVariables::screenResY, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
    screen = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    screenShiftX = GameVariables::screenResX / 2;
    screenShiftY = GameVariables::screenResY / 2;

    texturizer = new Texturizer(screen);
}

Renderer::~Renderer()
{
    //dtor
}

void Renderer::addPlayer(Player* playerin)
{
    player = playerin;
}

void Renderer::render()
{
    SDL_SetRenderDrawColor(screen, 0, 0, 0, 255);
    SDL_RenderClear(screen);

    //render stuff

    Renderable* renderable = player->getSs();
    SDL_Point center;

    SDL_Rect posrect;
    posrect.w = 128;
    posrect.h = 128;
    posrect.x = renderable->getX() + screenShiftX - (posrect.w / 2);
    posrect.y = renderable->getY() + screenShiftY - (posrect.h / 2);
    center.x = 64;
    center.y = 64;

    SDL_RenderCopyEx(screen, texturizer->loadTexture(renderable->getTex()), NULL, &posrect, renderable->getR(), &center, SDL_FLIP_NONE);

    SDL_RenderPresent(screen);
}
