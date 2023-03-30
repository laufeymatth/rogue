#include <string>
#include <stdlib.h>
#include <ncurses.h>

#include "person.h"

using namespace std;

void Person::setName(string name) {
    this->name = name;
}

string Person::getName() const {
    return this->name;
}

void Person::printPlayerBar(int rows, int cols, int floors, int killCount) {
    int life = this->getLife();
    int strength = this->getStrength();

    // print top box line
    mvprintw(rows - 1, 0, "+");
    for (int i = 0; i < cols; i++) {
        mvprintw(rows - 1, i + 1, "-");
    }
    mvprintw(rows - 1, cols + 1, "+");
    
    // print box contents
    mvprintw(rows, 0, "|");
    //name
    mvprintw(rows, 2, "Name:                      ");
    mvprintw(rows, 2, "Name: %s", this->getName().c_str());
    // life
    mvprintw(rows, cols / 5 * 1, "Life:                      ");
    mvprintw(rows, cols / 5 * 1, "Life: %i", life);
    // strength
    mvprintw(rows, cols / 5 * 2, "Strength:                      ");
    mvprintw(rows, cols / 5 * 2, "Strength: %i", strength);
    // number of floors
    mvprintw(rows, cols / 5 * 3, "Floors:                      ");
    mvprintw(rows, cols / 5 * 3, "Floors: %i", floors);
    // number of monsters killed
    mvprintw(rows, cols / 5 * 4, "Monsters Killed:                      ");
    mvprintw(rows, cols / 5 * 4, "Monsters Killed: %i", killCount);
    mvprintw(rows, cols + 1, "|");

    // print bottom box line
    mvprintw(rows + 1, 0, "+");
    for (int i = 0; i < cols; i++) {
        mvprintw(rows + 1, i + 1, "-");
    }
    mvprintw(rows + 1, cols + 1, "+");

}