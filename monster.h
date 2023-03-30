#ifndef MONSTER_H_
#define MONSTER_H_

#include <tuple>
#include "being.h"
#include "Person.h"
#include "pathfinding_DFS.h"

using namespace std;
class Monster: public Being {
    public:
        void takeAction(char** dungeon, Person player);
};

#endif