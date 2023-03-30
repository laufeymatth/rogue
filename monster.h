#ifndef MONSTER_H_
#define MONSTER_H_

#include <tuple>
#include "being.h"
#include "Person.h"
#include "pathfinding_DFS.h"
#include <cstdlib>
#include <ctime>

using namespace std;
class Monster: public Being {
    public:
        Monster(unsigned int seed_value = time(nullptr)) {
            seed = seed_value;
            srand(seed);
        }
        void takeAction(char** dungeon, Person player);

    private:
        unsigned int seed;
};

#endif