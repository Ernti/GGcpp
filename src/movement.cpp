#include "movement.h"

Movement::Movement()
{
    //ctor
}

Movement::~Movement()
{
    //dtor
}

void Movement::subscribe(std::function<bool()> callback)
{
    movelist.push_back(callback);
    std::cout << "move!" << std::endl;
}

void Movement::loop()
{
    for(unsigned int i = 0;i<movelist.size();i++)
    {
        if(!movelist[i]())
        {
            movelist.erase(movelist.begin() + i);
        }
    }
}
