#include "IslandThing.h"

IslandThing::IslandThing() : x(0), y(0), isShown(true)
{

}

IslandThing::~IslandThing()
{

}

int IslandThing::getX()
{
    return x;
}

void IslandThing::setX(int newX)
{
    x = newX;
}

int IslandThing::getY()
{
   return y;
}

void IslandThing::setY(int newY)
{
    y = newY;
}

bool IslandThing::getShown()
{
    return isShown;
}

void IslandThing::setShown(bool newShown)
{
    isShown = newShown;
}

int IslandThing::getDisplayChar()
{
    return displayChar;
}

void IslandThing::setDisplayChar(int newChar)
{
    displayChar = newChar;
}
