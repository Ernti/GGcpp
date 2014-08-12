#include "spaceship.h"

Spaceship::Spaceship(float x, float y) : Renderable(x, y)
{
    xrel = 0;
    xrel = 0;
}

Spaceship::~Spaceship()
{
    //dtor
}

void Spaceship::setTarget(float xin, float yin)
{
    target.clear();
    Target t;
    t.x = xin;
    t.y = yin;
    t.xrel = t.x - getX();
    t.yrel = t.y - getY();
    target.push_back(t);
    lasttick = SDL_GetTicks();
}

void Spaceship::addTarget(float xin, float yin)
{
    Target t;
    t.x = xin;
    t.y = yin;
    t.xrel = t.x - getX();
    t.yrel = t.y - getY();
    target.push_back(t);
    lasttick = SDL_GetTicks();
}

float Spaceship::getTargetX(int i = 0)
{
    if(target.size() > 0)
    {
        return target[i].x;
    }
    return getX();
}

float Spaceship::getTargetY(int i = 0)
{
    if(target.size() > 0)
    {
        return target[i].y;
    }
    return getY();
}

unsigned int Spaceship::getTargets()
{
    return target.size();
}

bool Spaceship::move()
{
    //std::cout << xrel << ", " << yrel << std::endl;

    //if(getX()!=target.x || getY()!=target.y)
    if(target[0].x - getX() > 1 || target[0].x - getX() < -1 || target[0].y - getY() > 1 || target[0].y - getY() < -1)
    {
        nowtick = SDL_GetTicks();

        target[0].xrel = target[0].x - getX();
        target[0].yrel = target[0].y - getY();
        xrel = cos(getR() * 3.14159265 / 180.);
        yrel = sin(getR() * 3.14159265 / 180.);

        turn();

        float xvel = 100. * (cos(getR() * 3.14159265 / 180.));
        float yvel = 100. * (sin(getR() * 3.14159265 / 180.));

        setX(getX() + xvel * ((nowtick - lasttick) / 1000.));
        setY(getY() + yvel * ((nowtick - lasttick) / 1000.));

        //std::cout << target.xrel << ", " << target.yrel << std::endl;

        lasttick = nowtick;
        return false;
    }
    target.erase(target.begin());
    return true;
}

void Spaceship::turn()
{
    xrel = target[0].xrel;
    yrel = target[0].yrel;
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

void Spaceship::turnRight()
{

}

void Spaceship::turnLeft()
{
    xrel = target[0].xrel - xrel / 10;
    yrel = target[0].yrel - yrel / 10;
}
