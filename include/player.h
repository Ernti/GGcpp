#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "spaceship.h"
#include "gamevariables.h"
#include "movement.h"
#include "packet.h"
#include <functional>

class Player
{
    public:
        Player(Movement*, Packet*, std::vector<Packet*>*);
        virtual ~Player();
        Spaceship* getSs();
        void setDestination(float, float, bool);
        float getX();
        void setX(float);
        float getY();
        void setY(float);
        float getZ();
        bool locked();
        void lock();
        void unlock();
        int camfollow();
        void zoom(int);
    protected:
    private:
        Movement* movement;
        Spaceship* spaceship;
        std::vector<Packet*>* broadcastlist;
        int id;
        float x;
        float y;
        float z;
        bool camlock;
};

#endif // PLAYER_H
