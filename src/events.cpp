#include "events.h"

Events::Events()
{
    //ctor
}

Events::~Events()
{
    //dtor
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

        }
        else if(event.type == SDL_KEYUP)
        {

        }
        else if(event.type == SDL_MOUSEBUTTONDOWN)
        {
            if(event.button.button == SDL_BUTTON_LEFT)
            {

            }
        }
    }
}
