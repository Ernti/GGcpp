#ifndef PLAYER_H
#define PLAYER_H

#include "spaceship.h"
#include "gamevariables.h"

class Player
{
    public:
        Player();
        virtual ~Player();
        Spaceship* getSs();
        void setDestination(float, float);
    protected:
    private:
        Spaceship* spaceship;
        float x;
        float y;
};

#endif // PLAYER_H
