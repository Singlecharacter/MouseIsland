#include "IslandControl.h"

int main()
{
    IslandControl controller;

    controller.getInitialInput();

    controller.init_curses();

    controller.simulate();

    controller.logResults();

    return 0;
}
