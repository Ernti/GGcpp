#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <vector>
#include <functional>
#include "spaceship.h"

class Movement
{
    public:
        Movement();
        virtual ~Movement();
        void subscribe(std::function<bool()>);
        void loop();
    protected:
    private:
        std::vector<std::function<bool()>> movelist;
};

#endif // MOVEMENT_H
