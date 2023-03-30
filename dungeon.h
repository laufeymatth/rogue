#ifndef DUNGEON_H_
#define DUNGEON_H_

#include <string>
#include <ostream>
#include <vector>
#include <ncurses.h>

#include "person.h"

using namespace std;



class Dungeon {
    public:

    void buildDungeon();

    void readRooms();
    void printRooms();
    void printDungeon();
    void addTunnels();

    void handleMovement();

    Dungeon() {
        readRooms();
        this->dungeon = new char*[this->ROWS];
        for (int i = 0; i < this->ROWS; i++) {
            this->dungeon[i] = new char[this->COLS];
        }
    };

    protected:
        char** dungeon;
        vector<char**> rooms;
        int ROWS = 42;
        int COLS = 102;
        Person player;
        
};


#endif // DUNGEON_H_