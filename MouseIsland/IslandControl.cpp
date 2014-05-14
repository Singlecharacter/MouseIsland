#include "IslandControl.h"

IslandControl::IslandControl() : islandName(""),numberOfSims(0),catLeftCount(0),turnCounter(0),turnsRemaining(100),
                                 catStartX(0),catStartY(0),mouseStartX(0),mouseStartY(0),mouseInHole(false),catOnIsland(true),
                                 currentDeath(Mouse::NONE),islandHeight(0),islandWidth(0)
{
    mouse = new Mouse;
    cat = new Cat;
    //initialize island map and heatmap
    for(int i = 0;i<MAX_HEIGHT;i++)
    {
        for(int j = 0;j<MAX_WIDTH;j++)
        {
            islandArray[i][j] = 0;
            heatMap[i][j] = 0;
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
    for(int i = 0;i<foodStorage.size();i++)
    {
        delete foodStorage.at(i);
    }
    endwin();
}

void IslandControl::init_curses()
{
    initscr();
    curs_set(0);
    islandWin = newwin(25,80,0,0);
    nodelay(islandWin,true);
    start_color();
    init_pair(1,COLOR_GREEN,COLOR_BLACK);
    init_pair(2,COLOR_RED,COLOR_BLACK);
    init_pair(3,COLOR_YELLOW,COLOR_BLACK);
}

void IslandControl::simulate()
{
    randSeed = time(NULL);
    srand(randSeed);
    while(numberOfSims > 0)
    {
        resetSimulation();
        runSimulation();
        numberOfSims--;
    }
}

void IslandControl::runSimulation()
{
    while(runOneFrame())
    {
        wait(1);
    }
    deathCounters[currentDeath] += 1;
}

void IslandControl::resetSimulation()
{
    mouse->setX(mouseStartX);
    mouse->setY(mouseStartY);

    cat->setX(catStartX);
    cat->setY(catStartY);
    cat->setShown(true);

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
    int prevCatX = cat->getX();
    int prevCatY = cat->getY();

    printIsland();
    int mouseDir = rand() % 3;
    int catDir = rand() % 3;

    if(mouseDir == 0) //right
    {
        mouse->setX(mouse->getX()+1);
    }
    else if(mouseDir == 1) //up
    {
        mouse->setY(mouse->getY()-1);
    }
    else if(mouseDir == 2) //left
    {
        mouse->setX(mouse->getX()-1);
    }
    else if(mouseDir == 3) //down
    {
        mouse->setY(mouse->getY()+1);
    }

    if(catOnIsland)
    {
        if(catDir == 0) //right
        {
            cat->setX(cat->getX()+1);
        }
        else if(catDir == 1) //up
        {
            cat->setY(cat->getY()-1);
        }
        else if(catDir == 2) //left
        {
            cat->setX(cat->getX()-1);
        }
        else if(catDir == 3) //down
        {
            cat->setY(cat->getY()+1);
        }
    }

    int mouseX = mouse->getX();
    int mouseY = mouse->getY();
    int catX = cat->getX();
    int catY = cat->getY();

    if(islandArray[catY][catX] == '~')
    {
        cat->setY(prevCatY);
        cat->setX(prevCatX);
    }

    if(catX == 0 || catX == islandWidth-1 || catY == 0 || catY == islandHeight - 1)
    {
        if(islandArray[catY][catX] == ACS_BLOCK)
        {
            cat->setShown(false);
            catOnIsland = false;
        }
    }

    turnCounter++;
    turnsRemaining--;

    if(turnsRemaining == 0)
    {
        currentDeath = Mouse::STARVED;
        return false;
    }

    if(islandArray[mouseY][mouseX] == 'o')//hole
    {
        mouseInHole = true;
    }
    else if(islandArray[mouseY][mouseX] == ACS_BLOCK)
    {
        currentDeath = Mouse::NONE;
        return false;
    }
    else if(islandArray[mouseY][mouseX] == '~')
    {
        currentDeath = Mouse::DROWNED;
        return false;
    }

    if(!mouseInHole && catOnIsland)
    {
        if(catX == mouseX && catY == mouseY)
        {
            currentDeath = Mouse::EATEN;
            return false;
        }
    }
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

    std::getline(island,islandName);
    island >> startSims;
    numberOfSims = startSims;

    island >> islandHeight;
    island >> islandWidth;
    for(int i = 0;i<islandHeight;i++)
    {
        for(int j = 0;j<islandWidth;j++)
        {
            island >> islandArray[i][j];
        }
    }

    island.close();

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
                islandArray[i][j] = '.';
                temp = new IslandThing;
                temp->setDisplayChar('F');
                foodStorage.push_back(temp);
            }
            else if(islandArray[i][j] == 4)
            {
                islandArray[i][j] = 'o';
            }
            else if(islandArray[i][j] < 0)
            {
                islandArray[i][j] = '~';
            }
            else
            {
                islandArray[i][j] = '.';
            }
        }
    }
}

void IslandControl::printIsland()
{
    wclear(islandWin);
    for(int i = 0;i<islandHeight;i++)
    {
        for(int j = 0;j<islandWidth;j++)
        {
            wmove(islandWin,i,j);
            waddch(islandWin,islandArray[i][j]);
        }
    }

    wmove(islandWin,mouse->getY(),mouse->getX());
    waddch(islandWin,mouse->getDisplayChar());

    wmove(islandWin,cat->getY(),cat->getX());
    waddch(islandWin,cat->getDisplayChar());

    /*for(int i = 0;i<foodStorage.size();i++)
    {
        wmove(islandWin,foodStorage.at(i)->getY(),foodStorage.at(i)->getX());
        waddch(islandWin,foodStorage.at(i)->getDisplayChar());
    }*/

    wrefresh(islandWin);
}

void IslandControl::logResults()
{
    std::ofstream outFile;
    outFile.open("log.txt",std::ofstream::app);

    outFile << islandName << std::endl;
    outFile << startSims << std::endl;
    outFile << randSeed << std::endl;

    outFile.close();
}

void IslandControl::wait(int secs)
{
    clock_t endwait = clock() + secs*CLK_TCK;
    while(clock() < endwait)
    {

    }
}
