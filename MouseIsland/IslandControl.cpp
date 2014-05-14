#include "IslandControl.h"

IslandControl::IslandControl() : islandName(""),numberOfSims(0),catLeftCount(0),turnCounter(0),turnsRemaining(100),
                                 catStartX(0),catStartY(0),mouseStartX(0),mouseStartY(0),mouseInHole(false),catOnIsland(true),
                                 currentDeath(Mouse::NONE),islandHeight(0),islandWidth(0)
{
    //initialize island map
    for(int i = 0;i<MAX_HEIGHT;i++)
    {
        for(int j = 0;j<MAX_WIDTH;j++)
        {
            islandArray[i][j] = 0;
        }
    }

    //initialize death counters
    for(int i = 0;i<Mouse::NUM_DEATH_TYPES;i++)
    {
        deathCounters[i] = 0;
    }
}

IslandControl::~IslandControl()
{

}

void IslandControl::simulate()
{
    randSeed = time(NULL);
    srand(randSeed);
    while(numberOfSims > 0)
    {
        runSimulation();
        resetSimulation();
        numberOfSims--;
    }
}

void IslandControl::runSimulation()
{
    while(runOneFrame());
    deathCounters[currentDeath] += 1;
}

void IslandControl::resetSimulation()
{
    mouse->setX(mouseStartX);
    mouse->setY(mouseStartY);

    cat->setX(catStartX);
    cat->setY(catStartY);

    mouseInHole = false;
    catOnIsland = true;
    turnsRemaining = 100;

    for(int i = 0;i<foodStorage.size();i++)
    {
        foodStorage.at(i)->setShown(true);
    }

}

bool IslandControl::runOneFrame()
{

}

void IslandControl::getInitialInput()
{
    std::string inString = "";
    std::ifstream inFile;
    while(true)
    {
        inString = getString("Enter a file name: ");
        inFile.open(inString.c_str());
        if(inFile.is_open())
        {
            inFile.close();
            break;
        }
        else
        {
            std::cout << "Bad file name. Try again."  << std::endl;
        }
    }

    loadIsland(inString);
}

bool IslandControl::loadIsland(std::string fileName)
{
    std::ifstream island;
    island.open(fileName.c_str());

    island >> islandName;
    island >> numberOfSims;

    island >> islandHeight;
    island >> islandWidth;
    for(int i = 0;i<islandHeight;i++)
    {
        for(int j = 0;j<islandWidth;j++)
        {
            island >> islandArray[i][j];
        }
    }

    IslandThing *temp;
    for(int i = 0;i<islandHeight;i++)
    {
        for(int j = 0;j<islandWidth;j++)
        {
            if(islandArray[i][j] == 0)
            {
                if(i == 0 || i == islandHeight-1 || j == 0 || j == islandWidth-1)
                {
                    islandArray[i][j] = ACS_BLOCK;
                }
                else
                {
                    islandArray[i][j] = '.';
                }
            }
            else if(islandArray[i][j] == 1)
            {
                mouseStartX = j;
                mouseStartY = i;
                islandArray[i][j] = '.';
            }
            else if(islandArray[i][j] == 2)
            {
                catStartX = j;
                catStartY = i;
                islandArray[i][j] = '.';
            }
            else if(islandArray[i][j] == 3)
            {

            }
            else if(islandArray[i][j] == 4)
            {

            }
            else
            {

            }
        }
    }
}

void IslandControl::printIsland()
{

}

void IslandControl::logResults()
{

}

void IslandControl::wait(int secs)
{
    int start = time(NULL);
    while(time(NULL) < start + secs);
}
