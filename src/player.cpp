#include "player.h"

Player::Player()
{
    spaceship = new Spaceship(0., 0.);
    x = 0;
    y = 0;
}

Player::~Player()
{
    //dtor
}
Spaceship* Player::getSs()
{
    return spaceship;
}

void Player::setDestination(float xin, float yin)
{
    spaceship->setX(x + xin - GameVariables::screenResX / 2);
    spaceship->setY(y + yin - GameVariables::screenResY / 2);
}
