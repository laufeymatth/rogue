#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <ncurses.h>
#include "dungeon.h"

using namespace std;

int SMALLROWS = 21;
int SMALLCOLS = 51;

void Dungeon::readRooms() {
    ifstream file("rooms51x11.txt");

    if (!file.is_open()) {
        printw("File not found.");
        return;
    }

    int matrix_count = 0;
    string line;

    while (getline(file, line)){
        matrix_count++;
    }

    file.clear();
    file.seekg(0, ios::beg);
    
    // matrix_count = matrix_count/SMALLCOLS;

    //add empty matrixes to this->rooms
    for (int i = 0; i < matrix_count / SMALLROWS; i++) {
        char** matrix = new char*[SMALLROWS];
        for (int j = 0; j < SMALLROWS; j++) {
            matrix[j] = new char[SMALLCOLS];
        }
        this->rooms.push_back(matrix);
    }

    
    int roomIndex = 0;
    while (roomIndex < matrix_count / SMALLROWS) {
        for (int i = 0; i < SMALLROWS; i++) {
            for (int j = 0; j < SMALLCOLS; j++) {
                char ch;
                file >> ch;
                if (ch == '.' || ch == 'M' || ch == 'E') {
                    this->rooms[roomIndex][i][j] = ' ';
                } else if (ch == 'x') {
                    this->rooms[roomIndex][i][j] = 'X';
                } else if (ch == '#') {
                    this->rooms[roomIndex][i][j] = '#';
                }
            }
        }
        roomIndex++;
    }
    file.close();
}


void Dungeon::buildDungeon() {
    srand(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));

    // set player pos
    int centerY = SMALLCOLS/2;  // line
    int centerX = SMALLROWS/2; // height
    player.setPos(centerX, centerY);

    // get random room from rooms
    char** room1 = this->rooms[rand() % this->rooms.size()];
    char** room2 = this->rooms[rand() % this->rooms.size()];
    char** room3 = this->rooms[rand() % this->rooms.size()];
    char** room4 = this->rooms[rand() % this->rooms.size()];

    // build top left
    for (int i = 0; i < SMALLROWS; i++) {
        for (int j = 0; j < SMALLCOLS; j++) {
            this->dungeon[i][j] = room1[i][j];
            if (room1[i][j] == '#') {this->dungeon[i][j] = ' ';}
        }
    }

    // build top right
    for (int i = 0; i < SMALLROWS; i++) {
        for (int j = 0; j < SMALLCOLS; j++) {
            this->dungeon[i+SMALLROWS][j] = room2[i][j];
            if (room2[i][j] == '#') {this->dungeon[i+SMALLROWS][j] = ' ';}
        }
    }

    // build bottom left
    for (int i = 0; i < SMALLROWS; i++) {
        for (int j = 0; j < SMALLCOLS; j++) {
            this->dungeon[i][j+SMALLCOLS] = room3[i][j];
            if (room3[i][j] == '#') {this->dungeon[i][j+SMALLCOLS] = ' ';}
        }
    }

    // build bottom right
    for (int i = 0; i < SMALLROWS; i++) {
        for (int j = 0; j < SMALLCOLS; j++) {
            this->dungeon[i+SMALLROWS][j+SMALLCOLS] = room4[i][j];
        }
    }

    addTunnels();
    printDungeon();
}

void Dungeon::addTunnels() {
    int centerY = SMALLCOLS/2;  // line
    int centerX = SMALLROWS/2; // height
    
    // loop to make tunnels left and right
    int tempCenterX = centerX;
    bool flag = false;
    for (int j = 0; j < 2; j++) {
        for (int i = 1; i < SMALLCOLS; i++){ //TODO change i= 1 to i = 0 when center != X
            if (this->dungeon[tempCenterX][centerY + i] == 'X') {
                if (!flag) {flag = true;}
                else {
                    // this->dungeon[tempCenterX][centerY + i] = '#';
                    this->dungeon[tempCenterX][centerY + i] = ' ';
                    this->dungeon[tempCenterX+1][centerY + i] = 'X';
                    this->dungeon[tempCenterX-1][centerY + i] = 'X';
                    flag = false; 
                    break;
                }
            }  
            if (flag) {
                this->dungeon[tempCenterX][centerY + i] = ' ';
                this->dungeon[tempCenterX+1][centerY + i] = 'X';
                this->dungeon[tempCenterX-1][centerY + i] = 'X';
            }
        }
    tempCenterX = tempCenterX + SMALLROWS;
    }


    // make tunnels up and down
    for (int j = 0; j < 2; j++) {
        for (int i = 1; i < SMALLROWS; i++){ //TODO change i= 1 to i = 0 when center != X
            if (this->dungeon[centerX + i][centerY] == 'X') {
                if (!flag) {flag = true;}
                else {
                    // this->dungeon[centerX + i][centerY] = '#';
                    this->dungeon[centerX + i][centerY] = ' ';
                    this->dungeon[centerX + i][centerY+1] = 'X';
                    this->dungeon[centerX + i][centerY-1] = 'X';
                    flag = false; 
                    break;
                }
            }  
            if (flag) {
                // this->dungeon[centerX + i][centerY] = '#';
                this->dungeon[centerX + i][centerY] = ' ';
                this->dungeon[centerX + i][centerY+1] = 'X';
                this->dungeon[centerX + i][centerY-1] = 'X';
            }
        }
    centerY = centerY + SMALLCOLS;
    }

    // add stairs down
    // this->dungeon[SMALLROWS/2+SMALLROWS][SMALLCOLS/2+SMALLCOLS] = '#';
}


void Dungeon::printRooms() {
    for (int index = 0; index < this->rooms.size(); index++) {
        for (int i = 0; i < SMALLROWS; i++) {
            for (int j = 0; j < SMALLCOLS; j++) {
                printw("%c ", this->rooms[index][i][j]);
            }
            printw("\n");
        }
    }
}

void Dungeon::printDungeon() {
    tuple <int, int> pos = player.getPos();
    clear();
    for (int i = 0; i < SMALLROWS*2; i++) {
        for (int j = 0; j < SMALLCOLS*2; j++) {
            if (i == get<0>(pos) && j == get<1>(pos)) {
                mvaddch(i, j, player.getToken());
            } else {
                mvaddch(i, j, this->dungeon[i][j]);
            }
        }
    }
    refresh();
}


// --------------------------------------- PLAYER

// arrow keys
enum ArrowKeys {
    UP = 65,
    DOWN = 66,
    LEFT = 68,
    RIGHT = 67,
    QUIT = 113 // q
};

void Dungeon::handleMovement() {
    player.setName("Player123"); //temp
    player.setLife(100); //temp
    player.setStrength(20); //temp
    while(1)
    {
        player.printPlayerBar(SMALLROWS*2, SMALLCOLS*2, getFloorCount());
        int ch = getch();
        switch(ch) {
        case UP:            
            player.moveUp(this->dungeon);
            break;
        case DOWN:
            player.moveDown(this->dungeon, SMALLROWS*2);
            break;
        case LEFT:
            player.moveLeft(this->dungeon);
            break;
        case RIGHT:
            player.moveRight(this->dungeon, SMALLCOLS*2);
            break;
        case QUIT:
            return;
        default:
            break;
        }
        // printDungeon();
        tuple <int, int> pos = player.getPos();
        if (this->dungeon[get<0>(pos)][get<1>(pos)] == '#'){
            upFLoorCount();
            buildDungeon();
        }
    }
}

void Dungeon::upFLoorCount() {
    this->floors = this->floors + 1;
}

int Dungeon::getFloorCount() {
    return this->floors;
}


