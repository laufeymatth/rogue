#ifndef DUNGEON_H_
#define DUNGEON_H_

#include <string>
#include <ostream>
#include <vector>

using namespace std;



class Dungeon {
    public:

    void buildDungeon();

    void readRooms();
    void printRooms();

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
        int ROWS = 22;
        int COLS = 22;
};


#endif // DUNGEON_H_