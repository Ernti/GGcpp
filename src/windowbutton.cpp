#include "windowbutton.h"

WindowButton::WindowButton()
{
    //ctor
}

WindowButton::~WindowButton()
{
    //dtor
}

SDL_Rect* WindowButton::getRect()
{
    return &rect;
}
