#include "monster.h"
#include "dungeon.h"
#include <ncurses.h>


void Monster::takeAction(char **dungeon, Person * player)
{
    bool isLeft = (std::get<0>(player->getPos()) < std::get<0>(this->pos)) ? true : false;
    bool isAbove = (std::get<1>(player->getPos()) < std::get<1>(this->pos)) ? true : false;

    int xdiff = std::get<1>(player->getPos()) - std::get<1>(this->pos);
    int ydiff = std::get<0>(player->getPos()) - std::get<0>(this->pos);
    
    if (abs(xdiff) <= 1 && abs(ydiff) <= 1)
    {
        // Takes The attack action
        player->setLife(player->getLife() - this->getStrength());
        return;
    }

    if (abs(xdiff) <= 10 && abs(ydiff) <= 10)
    {
        if (abs(xdiff) > abs(ydiff))
        {
            // Player is to the left or right
            if (xdiff > 0)
            {
                this->moveRight(dungeon, SMALLCOLS * 2);
            }
            else
            {
                this->moveLeft(dungeon);
            }
        }
        else
        {
            // # Player is above or below
            if (ydiff > 0)
            {
                this->moveDown(dungeon, SMALLCOLS * 2);
            }
            else
            {
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