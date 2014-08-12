#include "events.h"

Events::Events()
{
    movecam = false;
    shift = false;
}

Events::~Events()
{
    //dtor
}

void Events::addPlayer(Player* playerin)
{
    player = playerin;
}

void Events::eventLoop()
{
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            GameVariables::running = false;
        }
        else if(event.type == SDL_KEYDOWN)
        {
            if(event.key.keysym.scancode == SDL_SCANCODE_SPACE)
            {
                if(player->locked())
                {
                    player->unlock();
                }
                else
                {
                    player->lock();
                }

            }
            else if(event.key.keysym.scancode == SDL_SCANCODE_LSHIFT)
            {
                shift = true;
            }
        }
        else if(event.type == SDL_KEYUP)
        {
            if(event.key.keysym.scancode == SDL_SCANCODE_LSHIFT)
            {
                shift = false;
            }
        }
        else if(event.type == SDL_MOUSEBUTTONDOWN)
        {
            if(event.button.button == SDL_BUTTON_RIGHT)
            {
                float x = event.motion.x - GameVariables::screenResX / 2;
                float y = event.motion.y - GameVariables::screenResY / 2;
                player->setDestination(x, y, shift);
                std::cout << x << ", " << y << std::endl;
                std::cout << player->getX() << ", " << player->getY() << std::endl;
                std::cout << player->getSs()->getX() << ", " << player->getSs()->getY() << std::endl;
            }
            else if(event.button.button == SDL_BUTTON_LEFT)
            {
                if(player->locked())
                {
                    player->unlock();
                }
                movecam = true;

            }
        }
        else if(event.type == SDL_MOUSEBUTTONUP)
        {
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                movecam=false;
            }
        }
        else if(event.type == SDL_MOUSEWHEEL)
        {
            player->zoom(event.wheel.y);
        }
        else if(event.type == SDL_MOUSEMOTION)
        {
            if(movecam)
            {
                float x = player->getX() - event.motion.xrel * player->getZ();
                float y = player->getY() - event.motion.yrel * player->getZ();
                player->setX(x);
                player->setY(y);
            }
        }

    }
}
