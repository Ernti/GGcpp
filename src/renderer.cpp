#include "renderer.h"

Renderer::Renderer()
{
    window = SDL_CreateWindow("GG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GameVariables::screenResX, GameVariables::screenResY, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
    screen = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    screenShiftX = GameVariables::screenResX / 2;
    screenShiftY = GameVariables::screenResY / 2;

    texturizer = new Texturizer(screen);
    userinterface = new UserInterface(screen);

    Window* testwindow = new Window();
    testwindow->getRect()->x = 20;
    testwindow->getRect()->y = 40;
    testwindow->getRect()->w = 200;
    testwindow->getRect()->h = 400;
    WindowBox* testbox = new WindowBox();
    testbox->getRect()->x = 10;
    testbox->getRect()->y = 10;
    testbox->getRect()->w = 180;
    testbox->getRect()->h = 380;
    WindowText* testtext = new WindowText();
    testtext->getRect()->x = 10;
    testtext->getRect()->y = 10;
    testtext->getRect()->w = 160;
    testtext->getRect()->h = 20;
    testbox->texts.push_back(testtext);
    testwindow->boxes.push_back(testbox);
    //userinterface->windows.push_back(testwindow);
}

Renderer::~Renderer()
{
    //dtor
}

void Renderer::addPlayer(Player* playerin)
{
    player = playerin;
}

void Renderer::addRenderObject(Renderable* renderable)
{
    renderlist.push_back(renderable);
}

void Renderer::render()
{
    SDL_SetRenderDrawColor(screen, 0, 0, 0, 255);
    SDL_RenderClear(screen);

    //render stuff


    float lastx = player->getSs()->getX();
    float lasty = player->getSs()->getY();

    for(unsigned int it = 0;it<player->getTargets();it++)
    {
        if(player->getTargetX(it) - player->getSs()->getX() > 1 || player->getTargetX(it) - player->getSs()->getX() < -1
           || player->getTargetY(it) - player->getSs()->getY() > 1|| player->getTargetY(it) - player->getSs()->getY() < -1)
        {
            SDL_SetRenderDrawColor(screen, 0, 255, 0, 255);
            SDL_RenderDrawLine(screen,
                               ((lastx - player->getX()) / player->getZ() + screenShiftX), ((lasty - player->getY()) / player->getZ() + screenShiftY),
                               ((player->getTargetX(it) - player->getX()) / player->getZ() + screenShiftX), ((player->getTargetY(it) - player->getY()) / player->getZ() + screenShiftY));
            SDL_SetRenderDrawColor(screen, 0, 0, 0, 255);
            lastx = player->getTargetX(it);
            lasty = player->getTargetY(it);
        }
    }

    for(unsigned int it = 0;it<renderlist.size();it++)
    {
        Renderable* renderable = renderlist[it];
        SDL_Point center;

        SDL_Rect posrect;
        posrect.w = 128 / player->getZ();
        posrect.h = 128 / player->getZ();
        posrect.x = (renderable->getX() - player->getX()) / player->getZ() + screenShiftX - (posrect.w / 2);
        posrect.y = (renderable->getY() - player->getY()) / player->getZ() + screenShiftY - (posrect.h / 2);
        center.x = 64 / player->getZ();
        center.y = 64 / player->getZ();

        SDL_RenderCopyEx(screen, texturizer->loadTexture(renderable->getTex()), NULL, &posrect, renderable->getR(), &center, SDL_FLIP_NONE);
    }
    /*
    Renderable* renderable = player->getSs();
    SDL_Point center;

    SDL_Rect posrect;
    posrect.w = 128 / player->getZ();
    posrect.h = 128 / player->getZ();
    posrect.x = (renderable->getX() - player->getX()) / player->getZ() + screenShiftX - (posrect.w / 2);
    posrect.y = (renderable->getY() - player->getY()) / player->getZ() + screenShiftY - (posrect.h / 2);
    center.x = 64;
    center.y = 64;

    SDL_RenderCopyEx(screen, texturizer->loadTexture(renderable->getTex()), NULL, &posrect, renderable->getR(), &center, SDL_FLIP_NONE);
    */

    userinterface->render();

    SDL_RenderPresent(screen);
}
