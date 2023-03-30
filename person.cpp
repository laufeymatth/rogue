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

void Person::printPlayerBar(int rows, int cols, int floors) {
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
    mvprintw(rows, 2, "Name: %s", this->getName().c_str());
    // life
    mvprintw(rows, cols / 5 * 1.4, "Life: %i", life);
    // strength
    mvprintw(rows, cols / 5 * 2.8, "Strength: %i", strength);
    // number of floors
    mvprintw(rows, cols / 5 * 4, "Floors: %i", floors);
    mvprintw(rows, cols + 1, "|");

    // print bottom box line
    mvprintw(rows + 1, 0, "+");
    for (int i = 0; i < cols; i++) {
        mvprintw(rows + 1, i + 1, "-");
    }
    mvprintw(rows + 1, cols + 1, "+");

}