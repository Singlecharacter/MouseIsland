#ifndef ISLANDCONTROL_H
#define ISLANDCONTROL_H

#include <curses.h>
#include <vector>
#include <string>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include "IslandThing.h"
#include "Animals.h"
#include "customio.h"

const int MAX_WIDTH = 20;
const int MAX_HEIGHT = 20;

class IslandControl
{
public:

    IslandControl();
    ~IslandControl();

    void simulate();
    void runSimulation();
    void resetSimulation();
    bool runOneFrame();

    void getInitialInput();
    bool loadIsland(std::string);

    void printIsland();

    void logResults();

    void wait(int);

private:

    Mouse *mouse;
    Cat *cat;

    std::string islandName;

    int numberOfSims,randSeed;
    int turnCounter,turnsRemaining;
    int catStartX,catStartY,mouseStartX,mouseStartY;
    int islandHeight,islandWidth;

    bool mouseInHole, catOnIsland;

    Mouse::deathType currentDeath;

    std::vector<IslandThing*> foodStorage;

    int islandArray[MAX_HEIGHT][MAX_WIDTH];
    int heatMap[MAX_HEIGHT][MAX_WIDTH];
    int deathCounters[Mouse::NUM_DEATH_TYPES];

    int catLeftCount;
};

#endif // ISLANDCONTROL_H
