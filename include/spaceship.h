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
        Spaceship(float, float, unsigned int);
        virtual ~Spaceship();
        unsigned int getId();
        void setId(unsigned int);
        void setTarget(float, float);
        float getTargetX(int = 0);
        float getTargetY(int = 0);
        bool move();
        bool getMoving();
    protected:
    private:
        unsigned int id;
        bool moving;
        Target target;
        //std::vector<Item*> inventory;
        //Target target;
        Uint32 lasttick;
        Uint32 nowtick;
        void turn();
        float xrel;
        float yrel;
        float xvel;
        float yvel;

};

#endif // SPACESHIP_H
