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
    target.x = xin;
    target.y = yin;
    target.xrel = target.x - getX();
    target.yrel = target.y - getY();
    lasttick = SDL_GetTicks();
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

        turn();

        /*if(target.xrel < xrel && target.yrel < yrel)
        {
            turnRight();
        }
        else if(target.xrel > xrel && target.yrel > yrel)
        {
            turnRight();
        }
        else if(target.xrel < xrel && target.yrel > yrel)
        {
            turnLeft();
        }
        else if(target.xrel > xrel && target.yrel < yrel)
        {
            turnLeft();
        }*/

        float xvel = 100. * (cos(getR() * 3.14159265 / 180.));
        float yvel = 100. * (sin(getR() * 3.14159265 / 180.));

        setX(getX() + xvel * ((nowtick - lasttick) / 1000.));
        setY(getY() + yvel * ((nowtick - lasttick) / 1000.));

        std::cout << target.xrel << ", " << target.yrel << std::endl;

        lasttick = nowtick;
        return false;
    }
    return true;
}

void Spaceship::turn()
{
    xrel += target.xrel - xrel;
    yrel += target.yrel - yrel;
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
    xrel = target.xrel - xrel / 10;
    yrel = target.yrel - yrel / 10;
}
