#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <SDL.h>
#include "SDL_ttf.h"
#include <cstring>
#include <iostream>
#include <vector>
#include "gamevariables.h"
#include "window.h"

class UserInterface
{
    public:
        UserInterface(SDL_Renderer*);
        virtual ~UserInterface();
        void render();
        std::vector<Window*> windows;
    protected:
    private:
        void renderChat();
        void renderWindows();
        TTF_Font *font;
        SDL_Renderer* screen;
        Uint32 chatblinktick;
        bool chatblink;
};

#endif // USERINTERFACE_H
