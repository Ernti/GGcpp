#ifndef PLAYER_H
#define PLAYER_H

#include "spaceship.h"

class Player
{
    public:
        Player();
        virtual ~Player();
        Spaceship* getSs();
    protected:
    private:
        Spaceship* spaceship;
};

#endif // PLAYER_H
