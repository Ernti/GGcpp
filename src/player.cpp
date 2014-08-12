#include "player.h"

Player::Player(Movement* movementin)
{
    movement = movementin;
    spaceship = new Spaceship(0., 0.);
    x = 0;
    y = 0;
    z = 1;
}

Player::~Player()
{
    delete spaceship;
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
    if(shift)
    {
        spaceship->addTarget(x + xin * z, y + yin * z);
    }
    else
    {
        spaceship->setTarget(x + xin * z, y + yin * z);
    }
    movement->subscribe(std::bind(&Spaceship::move, spaceship));
}

int Player:: camfollow()
{
    setX(spaceship->getX());
    setY(spaceship->getY());
    if(locked())
    {
        return false;
    }
    return true;
}

void Player::zoom(int zoomfactor)
{
    z -= zoomfactor;
    if(z < 1)
    {
        z = 1;
    }
}
