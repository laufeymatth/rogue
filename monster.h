#ifndef MONSTER_H_
#define MONSTER_H_

#include <tuple>
#include "being.h"

using namespace std;
class Monster: Being {
    public:
        tuple<int, int> curr_pos;
};

#endif