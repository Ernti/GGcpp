#ifndef WINDOWBUTTON_H
#define WINDOWBUTTON_H

#include <SDL.h>

class WindowButton
{
    public:
        WindowButton();
        virtual ~WindowButton();
        SDL_Rect* getRect();
    protected:
    private:
        SDL_Rect rect;
};

#endif // WINDOWBUTTON_H
