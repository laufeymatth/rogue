#include <string>
#include <stdlib.h>
#include "person.h"

using namespace std;

void Person::setName(string name) {
    this->name = name;
}

string Person::getName() const {
    return this->name;
}