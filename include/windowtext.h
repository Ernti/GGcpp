#ifndef WINDOWTEXT_H
#define WINDOWTEXT_H

#include <SDL.h>

class WindowText
{
    public:
        WindowText();
        virtual ~WindowText();
        SDL_Rect* getRect();
    protected:
    private:
        SDL_Rect rect;
};

#endif // WINDOWTEXT_H
