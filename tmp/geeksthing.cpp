#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

const int row = 5, col = 5;

bool isValid(int arr[row][col], int x, int y, bool visited[row][col]) {
    return (x >= 0 && x < row && y >= 0 && y < col && !visited[x][y] && arr[x][y] == 0);
}

bool isPathUtil(int arr[row][col], int x, int y, bool visited[row][col], vector<pair<int, int>>& path) {
    if (x == row - 1 && y == col - 1) {
        path.push_back(make_pair(x, y));
        return true;
    }

    if (isValid(arr, x, y, visited)) {
        visited[x][y] = true;
        path.push_back(make_pair(x, y));

        if (isPathUtil(arr, x + 1, y, visited, path))
            return true;
        if (isPathUtil(arr, x, y + 1, visited, path))
            return true;
        if (isPathUtil(arr, x - 1, y, visited, path))
            return true;
        if (isPathUtil(arr, x, y - 1, visited, path))
            return true;

        path.pop_back();
    }
    return false;
}

bool isPath(int arr[row][col], vector<pair<int, int>>& path) {
    bool visited[row][col];
    memset(visited, false, sizeof(visited));

    if (isPathUtil(arr, 0, 0, visited, path)) {
        reverse(path.begin(), path.end());
        return true;
    }

    return false;
}

int main() {
    char arr[row][col] = {
        { '.', '.', '.', '.', '.' },
        { '.', '#', '.', '.', '.' },
        { '.', '.', '.', '#', '.' },
        { '.', '.', '.', '.', '#' },
        { '#', '.', '.', '.', '.' }
    };

    vector<pair<int, int>> path;
    int int_arr[row][col];

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (arr[i][j] == '.')
                int_arr[i][j] = 0;
            else
                int_arr[i][j] = -1;
        }
    }

    if (isPath(int_arr, path)) {
        cout << "Yes\n";
        cout << "The path is:\n";
        for (int i = 0; i < path.size(); i++) {
            cout << "(" << path[i].first << ", " << path[i].second << ") ";
        }
        cout << endl;
    }
    else {
        cout << "No" << endl;
    }

    return 0;
}