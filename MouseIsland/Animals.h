#ifndef ANIMALS_H
#define ANIMALS_H

#include "IslandThing.h"

class Mouse : public IslandThing
{
public:

    Mouse();
    ~Mouse();

    enum deathType
    {
        DROWNED,
        STARVED,
        EATEN,
        NONE
    };
};

class Cat : public IslandThing
{
public:

    Cat();
    ~Cat();
};
#endif // ANIMAL_H
