#ifndef WINDOWBOX_H
#define WINDOWBOX_H

#include <SDL.h>
#include <vector>
#include "windowbutton.h"
#include "windowtext.h"

class WindowBox
{
    public:
        WindowBox();
        virtual ~WindowBox();
        SDL_Rect* getRect();
        std::vector<WindowButton*> buttons;
        std::vector<WindowText*> texts;
    protected:
    private:
        SDL_Rect rect;
};

#endif // WINDOWBOX_H
