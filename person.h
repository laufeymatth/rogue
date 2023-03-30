#ifndef PERSON_H_
#define PERSON_H_

#include <string>
#include <ostream>
#include <tuple>

#include "being.h"

using namespace std;

class Person: public Being {
public:
    string getName() const;
    void setName(string name);

    void printLifeBar(int rows, int cols);

    Person() {
        this->name = "Player";
        this->life = 100;
        this->strength = 10;
    }
    
protected:
    string name;
    int life;
    int strength;

};

#endif // PERSON_H_