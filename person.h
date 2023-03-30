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
    
protected:
    string name;
    int life;
    int strength;

};

#endif // PERSON_H_