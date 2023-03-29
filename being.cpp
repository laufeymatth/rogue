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