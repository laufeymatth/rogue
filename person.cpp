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

void Person::printLifeBar(int rows, int cols) {
    int life = this->getLife();
    int strength = this->getStrength();
    // int lifeBar = (life * 100) / strength;
    mvprintw(rows - 1, 0, "Life: %i", life);
}