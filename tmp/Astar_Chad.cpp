#include <iostream>
#include <vector>

using namespace std;

// Define the size of the matrix
const int ROWS = 6;
const int COLS = 6;

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

int manhattanDistance(Point p1, Point p2) {
    return abs(p1.row - p2.row) + abs(p1.col - p2.col);
}

// Define a recursive function to find all possible paths from the current point to the end point
#include <queue>

// Define a function to find all possible paths from the start point to the end point in the matrix, using the A* algorithm
vector<vector<Point>> findPaths(matrix_t& matrix, Point start, Point end) {
    vector<vector<Point>> paths;
    vector<Point> currPath;
    
    // Define a priority queue to store candidate paths, sorted by their total cost
    auto cmp = [](const pair<int, vector<Point>>& a, const pair<int, vector<Point>>& b) {
        return a.first > b.first;
    };
    priority_queue<pair<int, vector<Point>>, vector<pair<int, vector<Point>>>, decltype(cmp)> pq(cmp);
    
    // Initialize the priority queue with the starting point as the only candidate path
    currPath.push_back(start);
    pq.push(make_pair(manhattanDistance(start, end), currPath));
    
    while (!pq.empty()) {
        // Pop the path with the lowest total cost from the priority queue
        auto currPair = pq.top();
        pq.pop();
        currPath = currPair.second;
        Point curr = currPath.back();
        
        // If the current point is the end point, add the current path to the list of paths and continue exploring
        if (curr.row == end.row && curr.col == end.col) {
            paths.push_back(currPath);
            continue;
        }
        
        // Explore all possible directions (up, down, left, right)
        int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, 1, 0, -1};
        for (int i = 0; i < 4; i++) {
            int newRow = curr.row + dx[i];
            int newCol = curr.col + dy[i];
            if (isValid(newRow, newCol) && matrix[newRow][newCol] == 0) {
                // Calculate the cost of the new path and add it to the priority queue
                int newPathCost = currPath.size() + 1 + manhattanDistance(Point(newRow, newCol), end);
                vector<Point> newPath(currPath);
                newPath.push_back(Point(newRow, newCol));
                pq.push(make_pair(newPathCost, newPath));
            }
        }
    }
    
    return paths;
}

// Define the main function to find all possible paths from the start point to the end point in the matrix
// vector<vector<Point>> findPaths(matrix_t& matrix, Point start, Point end) {
//     vector<vector<Point>> paths;
//     vector<Point> currPath;
//     matrix[start.row][start.col] = 1;
//     findPaths(matrix, start, end, paths, currPath);
//     return paths;
// }

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
    matrix_t matrix = {{0, -1, 0, 0, 0, 0},
                       {0, -1, 0, 0, 0, 0},
                       {0, -1, 0, 0, 0, 0},
                       {0, -1, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0}};
    Point start(0, 0);
    Point end(5, 5);
    
    vector<vector<Point>> paths = findPaths(matrix, start, end);
    std::cout << paths.back().back().col << " " << paths.back().back().col << endl;
    return 0;
}
