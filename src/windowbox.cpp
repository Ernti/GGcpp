#include "windowbox.h"

WindowBox::WindowBox()
{
    //ctor
}

WindowBox::~WindowBox()
{
    //dtor
}

SDL_Rect* WindowBox::getRect()
{
    return &rect;
}
