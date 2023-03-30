#ifndef MONSTER_H_
#define MONSTER_H_

#include <tuple>
#include "being.h"
#include "pathfinding_DFS.h"

using namespace std;
class Monster: Being {
    public:
        void takeAction(tuple <int, int> pos);
};

#endif