#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <ncurses.h>
#include "dungeon.h"

using namespace std;

const int HEALTHPOTION = 2;
const int STRENGTHPOTION = 1;

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
    

    //add empty matrixes to this->rooms
    for (int i = 0; i < matrix_count / SMALLROWS; i++) {
        char** matrix = new char*[SMALLROWS];
        for (int j = 0; j < SMALLROWS; j++) {
            matrix[j] = new char[SMALLCOLS];
        }
        this->rooms.push_back(matrix);
    }

    // fill matrixes with correct information
    int roomIndex = 0;
    while (roomIndex < matrix_count / SMALLROWS) {
        for (int i = 0; i < SMALLROWS; i++) {
            for (int j = 0; j < SMALLCOLS; j++) {
                char ch;
                file >> ch;
                if (ch == '.' || ch == 'M' || ch == 'E') {
                    this->rooms[roomIndex][i][j] = ' ';
                } else {
                    this->rooms[roomIndex][i][j] = ch;
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
    int centerY = SMALLCOLS/2;
    int centerX = SMALLROWS/2;
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
            if (room1[i][j] == '#' || room1[i][j] == 'Z') {this->dungeon[i][j] = ' ';}
        }
    }

    // build top right
    for (int i = 0; i < SMALLROWS; i++) {
        for (int j = 0; j < SMALLCOLS; j++) {
            this->dungeon[i+SMALLROWS][j] = room2[i][j];
            if (room2[i][j] == '#') {this->dungeon[i+SMALLROWS][j] = ' ';}
            else if (room2[i][j] == 'Z') {
                this->monsters[0].setPos(i+SMALLROWS, j);
                this->dungeon[i+SMALLROWS][j] = ' ';
            }
        }
    }

    // build bottom left
    for (int i = 0; i < SMALLROWS; i++) {
        for (int j = 0; j < SMALLCOLS; j++) {
            this->dungeon[i][j+SMALLCOLS] = room3[i][j];
            if (room3[i][j] == '#') {this->dungeon[i][j+SMALLCOLS] = ' ';}
            else if (room3[i][j] == 'Z') {
                this->monsters[1].setPos(i, j+SMALLCOLS);
                this->dungeon[i][j+SMALLCOLS] = ' ';
            }
        }
    }

    // build bottom right
    for (int i = 0; i < SMALLROWS; i++) {
        for (int j = 0; j < SMALLCOLS;  j++) {
            this->dungeon[i+SMALLROWS][j+SMALLCOLS] = room4[i][j];
            if (room4[i][j] == 'Z') {
                this->monsters[2].setPos(i+SMALLROWS, j+SMALLCOLS);
                this->dungeon[i+SMALLROWS][j+SMALLCOLS] = ' ';
            }
        }
    }

    addTunnels();
    printDungeon();
}

void Dungeon::addTunnels() {
    int centerY = SMALLCOLS/2; 
    int centerX = SMALLROWS/2; 

    // loop to make tunnels left and right
    int tempCenterX = centerX;
    bool flag = false;
    for (int j = 0; j < 2; j++) {
        for (int i = 1; i < SMALLCOLS; i++){
            if (this->dungeon[tempCenterX][centerY + i] == 'X') {
                if (!flag) {flag = true;}
                else {
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
        for (int i = 1; i < SMALLROWS; i++){ 
            if (this->dungeon[centerX + i][centerY] == 'X') {
                if (!flag) {flag = true;}
                else {
                    this->dungeon[centerX + i][centerY] = ' ';
                    this->dungeon[centerX + i][centerY+1] = 'X';
                    this->dungeon[centerX + i][centerY-1] = 'X';
                    flag = false; 
                    break;
                }
            }  
            if (flag) {
                this->dungeon[centerX + i][centerY] = ' ';
                this->dungeon[centerX + i][centerY+1] = 'X';
                this->dungeon[centerX + i][centerY-1] = 'X';
            }
        }
    centerY = centerY + SMALLCOLS;
    }
}



void Dungeon::printDungeon() {
    tuple <int, int> pos = player.getPos();
    tuple <int, int> posMon1 = this->monsters[0].getPos();
    tuple <int, int> posMon2 = this->monsters[1].getPos();
    tuple <int, int> posMon3 = this->monsters[2].getPos();

    clear();
    for (int i = 0; i < SMALLROWS*2; i++) {
        for (int j = 0; j < SMALLCOLS*2; j++) {
            // player
            if (i == get<0>(pos) && j == get<1>(pos)) {
                mvaddch(i, j, player.getToken());

            // monsters
            } else if (i == get<0>(posMon1) && j == get<1>(posMon1)) {
                mvaddch(i, j, this->monsters[0].getToken());
            }
            else if (i == get<0>(posMon2) && j == get<1>(posMon2)) {
                mvaddch(i, j, this->monsters[1].getToken());
            }
            else if (i == get<0>(posMon3) && j == get<1>(posMon3)) {
                mvaddch(i, j, this->monsters[2].getToken());
            }

            // dungeon layout
            else {
                mvaddch(i, j, this->dungeon[i][j]);
            }
        }
        refresh();
    }
    
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

int Dungeon::handleMovement() {
    int ch = getch();

    tuple <int, int> poso = player.getPos();
    int x = get<0>(poso);
    int y = get<1>(poso);
    int monsterIndex;

    switch(ch) {
    case UP:
        monsterIndex = checkMonsterPos(x-1, y);
        if (monsterIndex != -1) {
            this->monsters[monsterIndex].setLife(this->monsters[monsterIndex].getLife() - player.getStrength());
        } else {
            player.moveUp(this->dungeon);
        }
        break;
    case DOWN:
        monsterIndex = checkMonsterPos(x+1, y);
        if (monsterIndex != -1) {
            this->monsters[monsterIndex].setLife(this->monsters[monsterIndex].getLife() - player.getStrength());
        } else {
            player.moveDown(this->dungeon, SMALLROWS*2);
        }
        break;
    case LEFT:
        monsterIndex = checkMonsterPos(x, y-1);
        if (monsterIndex != -1) {
            this->monsters[monsterIndex].setLife(this->monsters[monsterIndex].getLife() - player.getStrength());
        } else {
            player.moveLeft(this->dungeon);
        }
        break;
    case RIGHT:
        monsterIndex = checkMonsterPos(x, y+1);
        if (monsterIndex != -1) {
            this->monsters[monsterIndex].setLife(this->monsters[monsterIndex].getLife() - player.getStrength());
        } else {
            player.moveRight(this->dungeon, SMALLCOLS*2);
        }
        break;
    case QUIT:
        return 1;
    default:
        break;
    }

    tuple <int, int> pos = player.getPos();
    // returns 2 if the player is postioned on a #, stairs to next floor
    if (this->dungeon[get<0>(pos)][get<1>(pos)] == '#'){
        return 2;
    // get healthpotion
    } else if (this->dungeon[get<0>(pos)][get<1>(pos)] == 'H') {
        this->dungeon[get<0>(pos)][get<1>(pos)] = ' ';
        player.setLife(player.getLife() + HEALTHPOTION);
    // get strengthpotion
    } else if (this->dungeon[get<0>(pos)][get<1>(pos)] == 'S') {
        this->dungeon[get<0>(pos)][get<1>(pos)] = ' ';
        player.setStrength(player.getStrength() + STRENGTHPOTION);
    }
    return 0;
}

// adds one to the floor count
void Dungeon::upFloorCount() {
    this->floors = this->floors + 1;
}

// gets the floor count
int Dungeon::getFloorCount() {
    return this->floors;
}

// makes every monster in the dungeon take action
void Dungeon::handleMonsters() {
    for (int i = 0; i < 3; i++) {
        this->monsters[i].takeAction(this->dungeon, &this->player);
    }
}


// check if pos contains monster, if so return index of monster, else return -1
int Dungeon::checkMonsterPos(int x, int y) {
    tuple <int, int> pos = make_tuple(x, y);
    for (int i = 0; i < 3; i++) {
        if (pos == this->monsters[i].getPos()) {
            return i;
        }
    }
    return -1;
}
