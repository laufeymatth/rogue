#include <string>
#include <stdlib.h>
#include <ncurses.h>

#include "person.h"
// #include "monster.h"

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
    mvprintw(rows, 2, "Name:                      ");
    mvprintw(rows, 2, "Name: %s", this->getName().c_str());
    // life
    mvprintw(rows, cols / 5 * 1.4, "Life:                      ");
    mvprintw(rows, cols / 5 * 1.4, "Life: %i", life);
    // strength
    mvprintw(rows, cols / 5 * 2.8, "Strength:                      ");
    mvprintw(rows, cols / 5 * 2.8, "Strength: %i", strength);
    // number of floors
    mvprintw(rows, cols / 5 * 4, "Floors:                      ");
    mvprintw(rows, cols / 5 * 4, "Floors: %i", floors);
    mvprintw(rows, cols + 1, "|");

    // print bottom box line
    mvprintw(rows + 1, 0, "+");
    for (int i = 0; i < cols; i++) {
        mvprintw(rows + 1, i + 1, "-");
    }
    mvprintw(rows + 1, cols + 1, "+");

}


// void Person::attackMonster(Monster monster) {
//     int monsterLife = monster->getLife();
//     int playerStrength = this->getStrength();

//     // reduce monster life by player strength
//     if (monsterLife > 0) {
//         monster->setLife(monsterLife - playerStrength);
//     }

//     // if monster life is less than 0, set it to 0
//     if (monster->getLife() <= 0) {
//         monster->setLife(0);
//     }
// }