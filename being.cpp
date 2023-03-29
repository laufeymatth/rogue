#include <string>
#include <stdlib.h>
#include <tuple>
#include "being.h"

using namespace std;

void Being::setPos(int x, int y) {
    this->pos = make_tuple(x, y);
}

tuple <int, int> Being::getPos() const {
    return this->pos;
}

void Being::setLife(int life) {
    this->life = life;
}

int Being::getLife() const {
    return this->life;
}

void Being::setStrength(int strength) {
    this->strength = strength;
}

int Being::getStrength() const {
    return this->strength;
}


// Move functions
void Being::moveUp(char** matrix) {
    tuple <int, int> pos = this->getPos();
    int x = get<0>(pos);
    int y = get<1>(pos);
    if (x > 0) {
        if (matrix[x - 1][y] != WALL) {
            x--;
        } 
    }
    this->setPos(x, y);
}

void Being::moveDown(char** matrix, int rows) {
    tuple <int, int> pos = this->getPos();
    int x = get<0>(pos);
    int y = get<1>(pos);
    if (x < rows - 1) {
        if (matrix[x + 1][y] != WALL) {
            x++;
        }
    }
    this->setPos(x, y);
}

void Being::moveLeft(char** matrix) {
    tuple <int, int> pos = this->getPos();
    int x = get<0>(pos);
    int y = get<1>(pos);
    if (y > 0) {
        if (matrix[x][y - 1] != WALL) {
            y--;
        }
    }
    this->setPos(x, y);
}

void Being::moveRight(char** matrix, int cols) {
    tuple <int, int> pos = this->getPos();
    int x = get<0>(pos);
    int y = get<1>(pos);
    if (y < cols - 1) {
        if (matrix[x][y + 1] != WALL) {
            y++;
        }
    }
    this->setPos(x, y);
}
