#include "monster.h"

// void Monster::takeAction(tuple <int, int> pos) {
//     get<0>(this->pos);
//     get<1>(this->pos);
//     bool isLeft = (get<0>(this->pos) - get<0>(pos)) < 0;
//     bool isOver = (get<1>(this->pos) - get<1>(pos)) < 0;
// }

void Monster::takeAction(tuple <int, int> pos) {
    bool isLeft, isAbove;
    if (std::get<0>(pos) < std::get<0>(this->pos)) { isLeft = true; } 
    else { isLeft = false; }

    if (std::get<1>(pos) < std::get<1>(this->pos)) { isAbove = true; } 
    else { isAbove = false; }

    
}