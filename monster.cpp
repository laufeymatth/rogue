#include "monster.h"
#include "dungeon.h"
#include <ncurses.h>

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

void Monster::takeAction(char **dungeon, Person player)
{
    bool isLeft = (std::get<0>(player.getPos()) < std::get<0>(this->pos)) ? true : false;
    bool isAbove = (std::get<1>(player.getPos()) < std::get<1>(this->pos)) ? true : false;

    int xdiff = std::get<1>(player.getPos()) - std::get<1>(this->pos);
    int ydiff = std::get<0>(player.getPos()) - std::get<0>(this->pos);
    
    if (abs(xdiff) <= 1 && abs(ydiff) <= 1)
    {
        // Takes The attack action
        player.setLife(this->getStrength());
        return;
    }

    if (abs(xdiff) <= 10 && abs(ydiff) <= 10)
    {
        // mvprintw(50, 0, " ");
        if (abs(xdiff) > abs(ydiff))
        {
            // Player is to the left or right
            if (xdiff > 0)
            {
                mvprintw(50, 0, "R");
                this->moveRight(dungeon, SMALLCOLS * 2);
            }
            else
            {
                mvprintw(50, 0, "L");
                this->moveLeft(dungeon);
            }
        }
        else
        {
            // # Player is above or below
            if (ydiff > 0)
            {
                mvprintw(50, 0, "D");
                this->moveDown(dungeon, SMALLCOLS * 2);
            }
            else
            {
                mvprintw(50, 0, "U");
                this->moveUp(dungeon);
            }
        }
        return;
    }

    int random_number = (rand() % 4) + 1;
    switch (random_number)
    {
    case 1:
        this->moveUp(dungeon);
        break;
    case 2:
        this->moveDown(dungeon, SMALLCOLS * 2);
        break;
    case 3:
        this->moveLeft(dungeon);
        break;
    case 4:
        this->moveRight(dungeon, SMALLCOLS * 2);
        break;
    }
    return;
}