#include "events.h"

Events::Events()
{
    movecam = false;
    chatActive = false;
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
        else if(event.type == SDL_TEXTINPUT)
        {
            if(GameVariables::chatinput.size() < 15)
            {
                GameVariables::chatinput += event.text.text;
            }
        }
        else if(event.type == SDL_KEYDOWN)
        {
            if(event.key.keysym.sym == SDLK_SPACE)
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
            else if(event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_RETURN2)
            {
                if(GameVariables::chatActive)
                {
                    SDL_StopTextInput();
                    GameVariables::setChatmessage();
                    GameVariables::chatActive = false;
                }
                else
                {
                    SDL_StartTextInput();
                    GameVariables::chatActive = true;
                }
            }
            else if(event.key.keysym.sym == SDLK_BACKSPACE)
            {
                if(GameVariables::chatinput.size() > 0)
                {
                    GameVariables::chatinput.pop_back();
                }
            }
            else if(event.key.keysym.sym == SDLK_LSHIFT)
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
