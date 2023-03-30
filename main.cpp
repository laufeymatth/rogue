#include <iostream>
#include <ncurses.h>
#include <tuple>
#include <string>
#include <ostream>
#include <stdio.h>

#include "person.h"
#include "dungeon.h"

#define PLAYERTOKEN 'O'
#define MONSTERTOKEN 'Z'

using namespace std;

void game() {
    cout << "Welcome to the dungeon!" << endl;
    cout << "-----------------------" << endl;
    string name;
    cout << "Enter your name: ";
    cin >> name;
    cout << "-----------------------" << endl;
    cout << endl;
    cout << "Hello, " << name << "!" << endl;
    cout << "You are about to embark on a great adventure." << endl;
    cout << "You will be exploring a dungeon, and you will need to find the exit!" << endl;
    cout << "You will encounter monsters, and you will need to fight them!" << endl;
    cout << "You will also find items, and you will need to use them!" << endl;
    cout << "You will need to be careful, and you will need to be smart!" << endl;
    cout << "If you lose all your life points, you will die." << endl;
    cout << "Good luck, " << name << "!";
    cout << endl;
    cout << "Press enter to start your journey..." << endl;
    cin.ignore();
    cin.get();

    // ncurses setup
    initscr(); // Initialize ncurses
    noecho(); // Turn off echoing of characters
    cbreak(); // Turn on character buffering
    curs_set(0); // Turn off cursor

    Dungeon d;

    d.player.setName(name); 
    d.player.setLife(100);
    d.player.setStrength(2);
    d.player.setToken(PLAYERTOKEN);

    //set life of monsters
    for (int i = 0; i < 3; i++) {
        d.monsters[i].setLife(10);
        d.monsters[i].setStrength(1);
        d.monsters[i].setToken(MONSTERTOKEN);
    }

    d.buildDungeon();

    bool died = false;
    // Loop
    while (true)
    {
        d.player.printPlayerBar(SMALLROWS*2, SMALLCOLS*2, d.getFloorCount());
        mvprintw(SMALLROWS*2 + 2, 0, "Press Q to quit.");
        if (d.player.getLife() <= 0) {
            died = true;
            break;
        }
        int res = d.handleMovement();
        d.handleMonsters(); 
        if (res == 1) {
            // QUIT
            break;
        } else if (res == 2) {
            // NEXT FLOOR
            for (int i = 0; i < 3; i++) {
                d.monsters[i].setLife(10);
                d.monsters[i].setToken(MONSTERTOKEN);
            }
            d.upFloorCount();
            d.buildDungeon();
        }

        // check if zombies are dead
        for (int i = 0; i < 3; i++) {
            if (d.monsters[i].getLife() <= 0) {
                d.monsters[i].setToken('.');
                d.monsters[i].setPos(0, 0);
            }
        }
        refresh();
    }

    int floors = d.getFloorCount();

    // ncurses cleanup
    endwin(); // Clean up ncurses

    cout << "-----------------------" << endl;
    cout << endl;
    if (died) { cout << "You died!" << endl; }
    cout << "Wow, what an adventure!" << endl;
    cout << "You made it to floor " << floors << "!" << endl;
    cout << "Thanks for playing!" << endl;
}

int main(int argc, char *argv[]) {
    game();

    return 0;
}
