#include "player.h"

Player::Player(Movement* movementin, Packet * startPacket)
{
    movement = movementin;
    id = startPacket->id;
    spaceship = new Spaceship(startPacket->x, startPacket->y, id);
    x = startPacket->x;
    y = startPacket->y;
    z = 1;
}

Player::~Player()
{
    delete spaceship;
}

unsigned int Player::getId()
{
    return id;
}

Spaceship* Player::getSs()
{
    return spaceship;
}

float Player::getX()
{
    return x;
}

void Player::setX(float xin)
{
    x = xin;
}

float Player::getY()
{
    return y;
}

void Player::setY(float yin)
{
    y = yin;
}

float Player::getZ()
{
    return z;
}

bool Player::locked()
{
    return camlock;
}

void Player::lock()
{
    camlock = true;
    movement->subscribe(std::bind(&Player::camfollow, this));
}

void Player::unlock()
{
    camlock = false;
}

void Player::setDestination(float xin, float yin, bool shift)
{
    if(!shift)
    {
        target.clear();
    }
    Target t;
    t.x = x + xin * z;
    t.y = y + yin * z;
    target.push_back(t);
    movement->subscribe(std::bind(&Player::targeting, this));
}

bool Player::targeting()
{
    if(target.size() > 0)
    {
        if(target[0].x - spaceship->getX() > 1 || target[0].x - spaceship->getX() < -1 || target[0].y - spaceship->getY() > 1 || target[0].y - spaceship->getY() < -1)
        {
            return true;
        }
        else
        {
            target.erase(target.begin());
            return true;
        }
    }
    else
    {
        return false;
    }
}

float Player::getTargetX(int i)
{
    if(target.size() > 0)
    {
        return target[i].x;
    }
    return spaceship->getX();
}

float Player::getTargetY(int i)
{
    if(target.size() > 0)
    {
        return target[i].y;
    }
    return spaceship->getY();
}

unsigned int Player::getTargets()
{
    return target.size();
}

int Player:: camfollow()
{
    setX(spaceship->getX());
    setY(spaceship->getY());
    if(locked())
    {
        return true;
    }
    return false;
}

void Player::zoom(int zoomfactor)
{
    z -= zoomfactor;
    if(z < 1)
    {
        z = 1;
    }
}
