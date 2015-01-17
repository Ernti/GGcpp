#include "windowtext.h"

WindowText::WindowText()
{
    //ctor
}

WindowText::~WindowText()
{
    //dtor
}

SDL_Rect* WindowText::getRect()
{
    return &rect;
}
