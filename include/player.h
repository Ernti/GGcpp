#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "spaceship.h"
#include "gamevariables.h"
#include "movement.h"
#include <functional>

class Player
{
    public:
        Player(Movement*);
        virtual ~Player();
        Spaceship* getSs();
        void setDestination(float, float);
    protected:
    private:
        Movement* movement;
        Spaceship* spaceship;
        float x;
        float y;
        void test();
};

#endif // PLAYER_H
