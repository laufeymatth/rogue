#include "pathfinding_DFS.h"
#include <iostream>
#include <vector>

using namespace std;

// Define a function to check if a point is within the bounds of the matrix
bool isValid(int row, int col) {
    return (row >= 0 && row < ROWS && col >= 0 && col < COLS);
}

// Define a recursive function to find all possible paths from the current point to the end point
void findPaths(matrix_t& matrix, Point curr, Point end, vector<vector<Point>>& paths, vector<Point>& currPath) {
    // Add the current point to the current path
    currPath.push_back(curr);
    
    // If the current point is the end point, add the current path to the list of paths and return
    if (curr.row == end.row && curr.col == end.col) {
        //if (currPath.size() <= 5) { // Only consider paths with length <= 5
        paths.push_back(currPath);
        
        //}
        currPath.pop_back();
        return;
    }
    
    // Explore all possible directions (up, down, left, right)
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};
    for (int i = 0; i < 4; i++) {
        int newRow = curr.row + dx[i];
        int newCol = curr.col + dy[i];
        if (isValid(newRow, newCol) && matrix[newRow][newCol] == ' ') {
            matrix[newRow][newCol] = 1;
            findPaths(matrix, Point(newRow, newCol), end, paths, currPath);
            matrix[newRow][newCol] = 0;
        }
    }
    
    // Remove the current point from the current path and return
    currPath.pop_back();
}

// Define the main function to find all possible paths from the start point to the end point in the matrix
vector<vector<Point>> findPaths(matrix_t& matrix, Point start, Point end) {
    vector<vector<Point>> paths;
    vector<Point> currPath;
    matrix[start.row][start.col] = 1;
    findPaths(matrix, start, end, paths, currPath);
    return paths;
}

// Define a function to print a list of paths
Point findPath(matrix_t &matrix, Point start, Point end) {
    vector<vector<Point>> paths = findPaths(matrix, start, end);
    if (paths.size() > 0 && paths.front().size() > 1) {
        return paths.front()[1];
    }
    return Point(-1, -1);
}

// Define the main function to test the findPaths function
// int main() {
//     matrix_t matrix = { {' ', ' ', ' ', ' '},
//                         {'#', '#', ' ', ' '},
//                         {' ', ' ', ' ', '#'},
//                         {' ', ' ', ' ', ' '} };

//     Point start(0, 0);
//     Point end(3, 3);

//     Point new_pos = findPath(matrix, start, end);
    
//     std::cout << (new_pos).col << " " << (new_pos).row << endl;
//     return 0;
// }
