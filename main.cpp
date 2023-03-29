#include <iostream>
#include <ncurses.h> // arrow keys
#include <tuple>
#include <string>
#include <ostream>
#include <stdio.h>
using namespace std;

#include "person.h"
#include "dungeon.h"

using namespace std;


// arrow keys
enum ArrowKeys {
    UP = 65,
    DOWN = 66,
    LEFT = 68,
    RIGHT = 67,
    QUIT = 113 // q
};

#define WALL '#'
#define PLAYER 'O'

void printMatrix(char** matrix, int rows, int cols, Person& player, int ch) {
    tuple <int, int> pos = player.getPos();
    clear();
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == get<0>(pos) && j == get<1>(pos)) {
                // cout << PLAYER << " ";
                printw("%c ", PLAYER);
            } else {
                // cout << matrix[i][j] << " ";
                printw("%c ", matrix[i][j]);
            }
        }
        // cout << endl;
        printw("\n");
    }
    printw("%i ", ch);
    refresh();
}

void handleMovement(char** matrix, int rows, int cols, Person& player) {
    int c = 0;
    // char ch;

    while(1)
    {
        int ch = getch();
        switch(ch) {
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
        // system("cls"); // clear console
        printMatrix(matrix, rows, cols, player, ch);
        // cout << "Press Q to exit!" << endl;
    }
}

int main(int argc, char *argv[]) {
    int rows = 10;
    int cols = 10;
    Person player;

    // ncurses
    initscr(); // Initialize ncurses
    noecho(); // Turn off echoing of characters
    cbreak(); // Turn on character buffering
    // ncurses end

    Dungeon d;
    d.buildDungeon();
    d.printDungeon();
    d.addTunnels();
    d.printDungeon();

    // // create the char matrix
    // char** matrix = new char*[rows];
    // for (int i = 0; i < rows; i++) {
    //     matrix[i] = new char[cols];
    // }

    // // fill the char matrix with values
    // for (int i = 0; i < rows; i++) {
    //     for (int j = 0; j < cols; j++) {
    //         matrix[i][j] = '.';
    //     }
    // }

    // // add walls
    // for (int i = 0; i < rows; i++) {
    //     if (i == 1 || i == 4) {
    //         matrix[i][0] = WALL;
    //     }
    // }

    // print the char matrix using the printMatrix function
    // printMatrix(matrix, rows, cols, player, 0);

    // // // movement
    // handleMovement(matrix, rows, cols, player);


    // // free the memory allocated for the char matrix
    // for (int i = 0; i < rows; i++) {
    //     delete[] matrix[i];
    // }
    // delete[] matrix;

    // ncurses
    endwin(); // Clean up ncurses
    // ncurses end

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

