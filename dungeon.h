#ifndef DUNGEON_H_
#define DUNGEON_H_

#include <string>
#include <ostream>
#include <vector>
#include <ncurses.h>

#include "person.h"
#include "monster.h"

using namespace std;



class Dungeon {
    public:

    void buildDungeon();

    void readRooms();
    void printRooms();
    void printDungeon();
    void addTunnels();

    void handleMovement();
    void upFLoorCount();
    int getFloorCount();

    Dungeon() {
        readRooms();
        this->floors = 0;
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
        int floors;
        Monster monsters[3];
};


#endif // DUNGEON_H_