#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "renderable.h"
#include <iostream>
#include <vector>
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
        void addTarget(float, float);
        float getTargetX(int);
        float getTargetY(int);
        unsigned int getTargets();
        bool move();
    protected:
    private:
        std::vector<Target> target;
        //Target target;
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
