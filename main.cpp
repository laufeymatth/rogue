#include <iostream>
#include <ncurses.h> // arrow keys
#include <tuple>
#include <string>
#include <ostream>
#include <stdio.h>

#include "person.h"
#include "dungeon.h"

using namespace std;


int main(int argc, char *argv[]) {
    // ncurses
    initscr(); // Initialize ncurses
    noecho(); // Turn off echoing of characters
    cbreak(); // Turn on character buffering
    curs_set(0); // Turn off cursor
    // ncurses end

    Dungeon d;
    d.buildDungeon();
    d.printDungeon();
    d.addTunnels();
    d.printDungeon();
    d.handleMovement();

    // ncurses
    endwin(); // Clean up ncurses
    // ncurses end

    return 0;

}
