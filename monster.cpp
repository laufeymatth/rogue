#include "monster.h"
#include "dungeon.h"

// void Monster::takeAction(tuple <int, int> pos) {
//     get<0>(this->pos);
//     get<1>(this->pos);
//     bool isLeft = (get<0>(this->pos) - get<0>(pos)) < 0;
//     bool isOver = (get<1>(this->pos) - get<1>(pos)) < 0;
// }

// bool isLeft, isAbove;
// if (std::get<0>(pos) < std::get<0>(this->pos)) { isLeft = true; } 
// else { isLeft = false; }

// if (std::get<1>(pos) < std::get<1>(this->pos)) { isAbove = true; } 
// else { isAbove = false; }

void Monster::takeAction(char** dungeon, Person player) {

    bool isLeft =  (std::get<0>(player.getPos()) < std::get<0>(this->pos)) ? true : false;
    bool isAbove = (std::get<1>(player.getPos()) < std::get<1>(this->pos)) ? true : false;

    int xdiff = abs(std::get<0>(player.getPos()) - std::get<0>(this->pos));
    int ydiff = abs(std::get<1>(player.getPos()) - std::get<1>(this->pos));

    if (xdiff <= 1 && ydiff <= 1) {
        // Takes The attack action
        player.setLife(this->getStrength());
    } else if (xdiff <= 4 && ydiff <= 4) {
        // Sees the player and moves towards him.
        matrix_t matrix;
        int i = std::get<0>(this->pos);
        if (isAbove) {
            i = std::get<0>(player.getPos());
        }

        int j = std::get<1>(this->pos);
        if (isLeft) {
            j = std::get<1>(player.getPos());
        }

        for (int ii=0; ii < 4; ii++) {
            for (int jj=0; jj < 4; jj++) {
                matrix[ii][jj] = dungeon[ii + i][jj + j];
            }
        }

        Point start = Point(std::get<0>(this->pos) - i, std::get<1>(this->pos) - j);
        Point end = Point(std::get<0>(player.getPos()) - i, std::get<1>(player.getPos()) - j);
        
        Point next_pos = findPath(matrix, start, end);

        if (start.col < next_pos.col) { this->moveUp(dungeon); }
        //if (start.col > next_pos.col) { this->moveDown(dungeon, ); }
        
    } else {
        // move in a random direction
    }


}