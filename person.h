#ifndef PERSON_H_
#define PERSON_H_

#include <string>
#include <ostream>
#include <tuple>

using namespace std;

class Person {
public:
    string getName() const;
    void setName(string name);
    
protected:
    string name;
    int life;
    int strength;

};

#endif // PERSON_H_