#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include "dungeon.h"

using namespace std;

int SMALLROWS = 11;
int SMALLCOLS = 51;

void Dungeon::readRooms() {
    ifstream file("rooms51x11.txt");

    if (!file.is_open()) {
        cout << "File not found." << endl;
        return;
    }

    int matrix_count = 0;
    string line;

    while (getline(file, line)){
        matrix_count++;
    }
    cout << "Number of lines in text file: " << matrix_count/SMALLROWS << endl;

    file.clear();
    file.seekg(0, ios::beg);
    
    // matrix_count = matrix_count/SMALLCOLS;

    //add empty matrixes to this->rooms
    for (int i = 0; i < matrix_count / SMALLROWS; i++) {
        cout << "index of added empty matrix " << i << endl;
        char** matrix = new char*[SMALLROWS];
        for (int j = 0; j < SMALLROWS; j++) {
            matrix[j] = new char[SMALLCOLS];
        }
        this->rooms.push_back(matrix);
    }

    cout << "rooms len " << this->rooms.size() << endl;
    
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
                }
            }
        }
        roomIndex++;
    }
    file.close();
}


void Dungeon::buildDungeon() {
    srand(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
    cout << 3 + rand() % 5 << endl;

    // get random room from rooms
    char** room1 = this->rooms[rand() % this->rooms.size()];
    char** room2 = this->rooms[rand() % this->rooms.size()];
    char** room3 = this->rooms[rand() % this->rooms.size()];
    char** room4 = this->rooms[rand() % this->rooms.size()];

    // build top left
    for (int i = 0; i < SMALLROWS; i++) {
        for (int j = 0; j < SMALLCOLS; j++) {
            this->dungeon[i][j] = room1[i][j];
        }
    }

    // build top right
    for (int i = 0; i < SMALLROWS; i++) {
        for (int j = 0; j < SMALLCOLS; j++) {
            this->dungeon[i+SMALLROWS][j] = room2[i][j];
        }
    }

    // build bottom left
    for (int i = 0; i < SMALLROWS; i++) {
        for (int j = 0; j < SMALLCOLS; j++) {
            this->dungeon[i][j+SMALLCOLS] = room3[i][j];
        }
    }

    // build bottom right
    for (int i = 0; i < SMALLROWS; i++) {
        for (int j = 0; j < SMALLCOLS; j++) {
            this->dungeon[i+SMALLROWS][j+SMALLCOLS] = room4[i][j];
        }
    }
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
                    this->dungeon[tempCenterX][centerY + i] = '#';
                    flag = false; 
                    break;
                }
            }  
            if (flag) {
                this->dungeon[tempCenterX][centerY + i] = '#';
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
                    this->dungeon[centerX + i][centerY] = '#';
                    flag = false; 
                    break;
                }
            }  
            if (flag) {
                this->dungeon[centerX + i][centerY] = '#';
            }
        }
    centerY = centerY + SMALLCOLS;
    }
}


void Dungeon::printRooms() {
    for (int index = 0; index < this->rooms.size(); index++) {
        cout << index;
        for (int i = 0; i < SMALLROWS; i++) {
            for (int j = 0; j < SMALLCOLS; j++) {
                cout << this->rooms[index][i][j];
            }
            cout << endl;
        }
    }
}

void Dungeon::printDungeon() {
    for (int i = 0; i < SMALLROWS*2; i++) {
        for (int j = 0; j < SMALLCOLS*2; j++) {
            cout << this->dungeon[i][j];
        }
        cout << endl;
    }
}


