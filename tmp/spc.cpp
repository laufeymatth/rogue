#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1000000000; // A large enough value to represent "infinity"

int dijkstra(const vector<vector<char>>& matrix, int rows, int cols, int sx, int sy, int ex, int ey) {
    vector<vector<int>> dist(rows, vector<int>(cols, INF)); // Initialize all distances to "infinity"
    dist[sx][sy] = 0; // Set the distance of the start vertex to 0

    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
    pq.push({0, {sx, sy}}); // Add the start vertex to the priority queue

    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();

        int d = top.first;
        int x = top.second.first;
        int y = top.second.second;

        if (x == ex && y == ey) {
            return d; // Found the shortest path to the end vertex
        }

        if (d > dist[x][y]) {
            continue; // We have already found a shorter path to this vertex
        }

        // Check all neighbors of the current vertex
        int dx[] = {1, -1, 0, 0};
        int dy[] = {0, 0, 1, -1};
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 0 || nx >= rows || ny < 0 || ny >= cols || matrix[nx][ny] == '1') {
                continue; // Skip invalid or blocked cells
            }
            int nd = d + 1; // The distance to the neighbor is always 1
            if (nd < dist[nx][ny]) {
                dist[nx][ny] = nd;
                pq.push({nd, {nx, ny}}); // Add the neighbor to the priority queue
            }
        }
    }

    return -1; // There is no path from the start vertex to the end vertex
}

int main() {
    int rows = 5;
    int cols = 5;
    vector<vector<char>> matrix = {
        {'0', '1', '1', '1', '0'},
        {'0', '0', '1', '0', '0'},
        {'0', '0', '0', '1', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '1', '0', '0', '0'}
    };
    int sx = 0;
    int sy = 0;
    int ex = 4;
    int ey = 4;
    int shortest_path_length = dijkstra(matrix, rows, cols, sx, sy, ex, ey);
    if (shortest_path_length == -1) {
        cout << "There is no path from (" << sx << ", " << sy << ") to (" << ex << ", " << ey << ")" << endl;
    } else {
        cout << "The shortest path from (" << sx << ", " << sy << ") to (" << ex << ", " << ey << ") has length " << shortest_path_length << endl;
    }
    return 0;
}