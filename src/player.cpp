#include "player.h"

Player::Player(Movement* movementin)
{
    movement = movementin;
    spaceship = new Spaceship(0., 0.);
    x = 0;
    y = 0;
}

Player::~Player()
{
    delete spaceship;
}

Spaceship* Player::getSs()
{
    return spaceship;
}

void Player::setDestination(float xin, float yin)
{
    spaceship->setTarget(x + xin - GameVariables::screenResX / 2, y + yin - GameVariables::screenResY / 2);

    std::cout << "adding spaceship" << std::endl;
    movement->subscribe(std::bind(&spaceship->move, spaceship));
}

