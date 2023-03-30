#ifndef PATHFINDING_DFS_H_
#define PATHFINDING_DFS_H_

#include <iostream>
#include <vector>

using namespace std;

const int MATRX_ROWS = 4;
const int MATRX_COLS = 4;
typedef char matrix_t[MATRX_ROWS][MATRX_COLS];

struct Point {
    int row, col;
    Point(int r, int c) : row(r), col(c) {}
};

bool isValid(int row, int col);
void findPaths(matrix_t& matrix, Point curr, Point end, vector<vector<Point>>& paths, vector<Point>& currPath);
vector<vector<Point>> findPaths(matrix_t& matrix, Point start, Point end);
void printPaths(vector<vector<Point>>& paths);
Point findPath(matrix_t &matrix, Point start, Point end);

#endif