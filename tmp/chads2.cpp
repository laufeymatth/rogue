#include <iostream>
#include <vector>

using namespace std;

// Define the size of the matrix
const int ROWS = 6;
const int COLS = 6;
const int max_view = 8;

// Define the matrix type as a 2D array of integers
typedef int matrix_t[ROWS][COLS];

// Define a struct to represent a point in the matrix
struct Point {
    int row, col;
    Point(int r, int c) : row(r), col(c) {}
};

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
        if (currPath.size() <= max_view) { // Only consider paths with length <= 5
            paths.push_back(currPath);
        }
        currPath.pop_back();
        return;
    }
    
    // Explore all possible directions (up, down, left, right)
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};
    bool found = false;
    for (int i = 0; i < 4; i++) {
        int newRow = curr.row + dx[i];
        int newCol = curr.col + dy[i];
        if (isValid(newRow, newCol) && matrix[newRow][newCol] == 0) {
            matrix[newRow][newCol] = 1;
            findPaths(matrix, Point(newRow, newCol), end, paths, currPath);
            matrix[newRow][newCol] = 0;
            found = true;
        }
    }
    
    // If none of the directions lead to the end point, discard the current path
    if (!found) {
        currPath.pop_back();
        return;
    }
    
    // Remove the current point from the current path and return
    currPath.pop_back();
}

// Define a function to print a list of paths
void printPaths(vector<vector<Point>>& paths) {
    for (int i = 0; i < paths.size(); i++) {
        cout << "Path " << i + 1 << ": ";
        for (int j = 0; j < paths[i].size(); j++) {
            cout << "(" << paths[i][j].row << "," << paths[i][j].col << ")";
            if (j < paths[i].size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
    }
}

// Define the main function to test the findPaths function
int main() {
    matrix_t matrix = {{0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0}};
    Point start(0, 0);
    Point end(2, 3);
    vector<vector<Point>> paths;
    vector<Point> currPath;
    findPaths(matrix, start, end, paths, currPath);

    printPaths(paths);
    return 0;
}

