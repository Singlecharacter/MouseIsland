#include "IslandControl.h"

int main()
{
    IslandControl controller;

    controller.getInitialInput();

    controller.simulate();

    controller.logResults();

    return 0;
}
