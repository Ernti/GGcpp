#include "player.h"

Player::Player()
{
    spaceship = new Spaceship(0., 0.);
}

Player::~Player()
{
    //dtor
}
Spaceship* Player::getSs()
{
    return spaceship;
}
