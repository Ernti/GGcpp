#include "window.h"

Window::Window()
{
    //ctor
}

Window::~Window()
{
    //dtor
}

SDL_Rect* Window::getRect()
{
    return &rect;
}
