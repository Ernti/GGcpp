#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <vector>
#include "windowbox.h"

class Window
{
    public:
        Window();
        virtual ~Window();
        SDL_Rect* getRect();
        std::vector<WindowBox*> boxes;
    protected:
    private:
        SDL_Rect rect;
};

#endif // WINDOW_H
