#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "dungeon.h"

using namespace std;

int SMALLROWS = 11;
int SMALLCOLS = 11;

void Dungeon::readRooms() {
    ifstream file("room1.txt");

    if (!file.is_open()) {
        cout << "File not found." << endl;
        return;
    }

    int matrix_count = 0;
    string line;

    while (getline(file, line)){
        matrix_count++;
    }
    cout << "Number of lines in text file: " << matrix_count/11 << endl;

    file.clear();
    file.seekg(0, ios::beg);
    
    // matrix_count = matrix_count/SMALLCOLS;

    //add empty matrixes to this->rooms
    for (int i = 0; i < matrix_count / SMALLCOLS; i++) {
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
                if (ch == '0') {
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

void Dungeon::buildDungeon() {


}