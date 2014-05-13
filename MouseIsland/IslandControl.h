#ifndef ISLANDCONTROL_H
#define ISLANDCONTROL_H

#include <vector>
#include <string>
#include <ctime>
#include "IslandThing.h"
#include "Animals.h"

const int MAX_WIDTH = 20;
const int MAX_HEIGHT = 20;

class IslandControl
{
public:

    IslandControl();
    ~IslandControl();

    void runOneFrame();



private:

    Mouse mouse;
    Cat cat;

    std::vector<IslandThing> otherThings;

    int islandArray[MAX_HEIGHT][MAX_WIDTH];
};

#endif // ISLANDCONTROL_H
