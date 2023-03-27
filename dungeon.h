#ifndef DUNGEON_H_
#define DUNGEON_H_

#include <string>
#include <ostream>

using namespace std;

class Dungeon {
    public:

    void setWalls(char* walls);

    Dungeon() {
        this->walls = 0;
    }
};


#endif // DUNGEON_H_