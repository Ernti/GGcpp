#include "spaceship.h"

Spaceship::Spaceship(float x, float y, unsigned int idin) : Renderable(x, y)
{
    id = idin;
    xrel = 0;
    xrel = 0;
    target.x = x;
    target.y = y;
    moving = false;
}

Spaceship::~Spaceship()
{
    //dtor
}

unsigned int Spaceship::getId()
{
    return id;
}

void Spaceship::setId(unsigned int i)
{
    id = i;
}

void Spaceship::setTarget(float xin, float yin)
{
    Target t;
    t.x = xin;
    t.y = yin;
    t.xrel = t.x - getX();
    t.yrel = t.y - getY();
    target=t;
    lasttick = SDL_GetTicks();
}

float Spaceship::getTargetX(int i)
{
    return target.x;
}

float Spaceship::getTargetY(int i)
{
    return target.y;
}

bool Spaceship::getMoving()
{
    return moving;
}

bool Spaceship::move()
{
    //std::cout << xrel << ", " << yrel << std::endl;

    //if(getX()!=target.x || getY()!=target.y)
    if(target.x - getX() > 1 || target.x - getX() < -1 || target.y - getY() > 1 || target.y - getY() < -1)
    {
        nowtick = SDL_GetTicks();

        target.xrel = target.x - getX();
        target.yrel = target.y - getY();
        xrel = cos(getR() * 3.14159265 / 180.);
        yrel = sin(getR() * 3.14159265 / 180.);

        turn();

        float xvel = 100. * (cos(getR() * 3.14159265 / 180.));
        float yvel = 100. * (sin(getR() * 3.14159265 / 180.));

        setX(getX() + xvel * ((nowtick - lasttick) / 1000.));
        setY(getY() + yvel * ((nowtick - lasttick) / 1000.));

        //std::cout << target.xrel << ", " << target.yrel << std::endl;

        lasttick = nowtick;
        moving = true;
        return moving;
    }
    moving = false;
    return moving;
}

void Spaceship::turn()
{
    xrel = target.xrel;
    yrel = target.yrel;
    //xrel += target.xrel - xrel;
    //yrel += target.yrel - yrel;

    setR(atan2(yrel, xrel) * 180 / 3.14159265);
    if(getR() > 180)
    {
        setR(getR() - 360);
    }
    if(getR() < -180)
    {
        setR(getR() + 360);
    }
}
