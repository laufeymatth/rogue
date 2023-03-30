#ifndef DUNGEON_H_
#define DUNGEON_H_

#include <string>
#include <ostream>
#include <vector>
#include <ncurses.h>

#include "person.h"
#include "monster.h"

using namespace std;

const int SMALLROWS = 21;
const int SMALLCOLS = 51;

class Dungeon {
    public:
    Person player;
    Monster monsters[3];

    void buildDungeon();

    void readRooms();
    void printDungeon();
    void addTunnels();

    int handleMovement();
    void upFloorCount();
    int getFloorCount();
    void handleMonsters();

    int checkMonsterPos(int x, int y);

    Dungeon() {
        readRooms();
        this->floors = 0;
        this->dungeon = new char*[this->ROWS];
        for (int i = 0; i < this->ROWS; i++) {
            this->dungeon[i] = new char[this->COLS];
        }
        for (int i = 0; i < 3; i++) { // ---------------------3 monsters
            monsters[i].setToken('M');  
        } 
    };

    protected:
        char** dungeon;
        vector<char**> rooms;
        int ROWS = 42;
        int COLS = 102;
        int floors;
};


#endif // DUNGEON_H_