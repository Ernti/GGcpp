#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "renderable.h"
#include <iostream>
#include <math.h>
#include "SDL.h"


struct Target
{
    float x;
    float y;
    float xrel;
    float yrel;
};

class Spaceship : public Renderable
{
    public:
        Spaceship(float, float);
        virtual ~Spaceship();
        void setTarget(float, float);
        bool move();
    protected:
    private:
        Target target;
        Uint32 lasttick;
        Uint32 nowtick;
        void turnRight();
        void turnLeft();
        void turn();
        float xrel;
        float yrel;
        float xvel;
        float yvel;

};

#endif // SPACESHIP_H
