#ifndef PERSON_H_
#define PERSON_H_

#include <string>
#include <ostream>
#include <tuple>

#include "being.h"
// #include "monster.h"

using namespace std;

class Person: public Being {
public:
    string getName() const;
    void setName(string name);

    void printPlayerBar(int rows, int cols, int floors, int killCount);

    // void attackMonster(Monster monster);
    
protected:
    string name = "Player";

};

#endif // PERSON_H_