#ifndef BEING_H_
#define BEING_H_

#include <string>
#include <ostream>
#include <tuple>

using namespace std;

class Being {
public:
    tuple <int, int> getPos() const;
    void setPos(int x, int y);

    char getToken() const;
    void setToken(char token);

    int getLife() const;
    void setLife(int life);

    int getStrength() const;
    void setStrength(int strength);

    Being() {
        this->pos = make_tuple(0, 0);
        this->life = 0;
        this->strength = 0;
        this->TOKEN = 'O';
    }

    // Movement functions
    void moveUp(char** matrix);
    void moveDown(char** matrix, int rows);
    void moveLeft(char** matrix);
    void moveRight(char** matrix, int cols);
    
protected:
    tuple <int, int> pos;
    int life;
    int strength;
    char WALL = 'X'; 
    char TOKEN;

};

#endif // BEING_H_