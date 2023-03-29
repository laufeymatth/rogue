#include <iostream>
#include <conio.h> // arrow keys
#include <Windows.h> // clear console
#include <tuple>
#include <string>
#include <ostream>
using namespace std;

#include "person.h"
#include "dungeon.h"

using namespace std;

// arrow keys
enum ArrowKeys {
    UP = 72,
    DOWN = 80,
    LEFT = 75,
    RIGHT = 77,
    QUIT = 113 // q
};

#define WALL '#'
#define PLAYER 'O'

void printMatrix(char** matrix, int rows, int cols, Person& player) {
    tuple <int, int> pos = player.getPos();
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == get<0>(pos) && j == get<1>(pos)) {
                cout << PLAYER << " ";
            } else {
                cout << matrix[i][j] << " ";
            }
        }
        cout << endl;
    }
}

void handleMovement(char** matrix, int rows, int cols, Person& player) {
    int c = 0;
    
    while(1)
    {
        c = 0;
        tuple <int, int> pos = player.getPos();
        int x = get<0>(pos);
        int y = get<1>(pos);

        switch((c=getch())) {
        case UP:            
            player.moveUp(matrix);
            break;
        case DOWN:
            player.moveDown(matrix, rows);
            break;
        case LEFT:
            player.moveLeft(matrix);
            break;
        case RIGHT:
            player.moveRight(matrix, cols);
            break;
        case QUIT:
            return;
        default:
            break;
        }
        system("cls"); // clear console
        printMatrix(matrix, rows, cols, player);
        cout << "Press Q to exit!" << endl;
    }
}

int main(int argc, char *argv[]) {
    int rows = 10;
    int cols = 10;
    Person player;

    // create the char matrix
    char** matrix = new char*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new char[cols];
    }

    // fill the char matrix with values
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = '.';
        }
    }

    // add walls
    for (int i = 0; i < rows; i++) {
        if (i == 1 || i == 4) {
            matrix[i][0] = WALL;
        }
    }

    // print the char matrix using the printMatrix function
    printMatrix(matrix, rows, cols, player);

    // movement
    handleMovement(matrix, rows, cols, player);


    // free the memory allocated for the char matrix
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}


// int main(int argc, char *argv[]) {
//     Dungeon d;
//     d.printRooms();
// }


// ------------------------------------------------------------------------------------
// TODO

// decide objective of game, money? survive? get to other side?

// make 1 test dungeon, maybe it will be our last

// game loop where dungeon cleared and drawn new every time char moves.

// decide how monster moves? need math formula to know to move closer?? pythagorean?

// start ui

// b krafs:

// make battle possible

// make radomize dungeon func, maybe premade rooms randomly put together

// add magic items, lil booties make go fast.

