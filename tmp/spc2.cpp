#include <iostream>
#include <climits>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Represents an edge between two vertices.
struct Edge {
    int weight;
    int v;
};

// Finds the shortest path between two points in a graph using Dijkstra's algorithm.
vector<pair<int, int>> dijkstra(vector<vector<char>>& grid, int rows, int cols, int startX, int startY, int endX, int endY) {
    vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    // Convert the grid into a graph.
    vector<vector<Edge>> graph(rows * cols);
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] != '#') {
                int u = r * cols + c;
                for (pair<int, int> d : directions) {
                    int r2 = r + d.first, c2 = c + d.second;
                    if (r2 >= 0 && r2 < rows && c2 >= 0 && c2 < cols && grid[r2][c2] != '#') {
                        int v = r2 * cols + c2;
                        graph[u].push_back({1, v});
                    }
                }
            }
        }
    }

    // Initialize distance vector and priority queue.
    vector<int> distance(rows * cols, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Add the starting vertex to the queue.
    int start = startX * cols + startY;
    distance[start] = 0;
    pq.push({0, start});

    // Run Dijkstra's algorithm.
    while (!pq.empty()) {
        // Get the vertex with the smallest distance.
        int u = pq.top().second;
        pq.pop();

        // If we have reached the destination, return the path.
        if (u == endX * cols + endY) {
            vector<pair<int, int>> path;
            while (u != start) {
                path.push_back({u / cols, u % cols});
                u = distance[u - cols];
            }
            path.push_back({u / cols, u % cols});
            reverse(path.begin(), path.end());
            return path;
        }

        // Mark the vertex as visited and update the distances of its neighbors.
        for (Edge e : graph[u]) {
            int v = distance[u] + e.weight;
            if (v < distance[e.v]) {
                distance[e.v] = v;
                pq.push({v, e.v});
            }
        }
    }

    // No path was found.
    return {};
}

int main() {
    int rows, cols, start_row, start_col, end_row, end_col;
    cin >> rows >> cols >> start_row >> start_col >> end_row >> end_col;
    vector<vector<char>> grid(rows, vector<char>(cols));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> grid[i][j];
        }
    }
    vector<pair<int, int>> result = dijkstra(grid, rows, cols, start_row, start_col, end_row, end_col);
    if (result.empty()) {
        cout << "No path found" << endl;
    } else {
        cout << "Shortest path: ";
        reverse(result.begin(), result.end());
        for (pair<int, int> p : result) {
            cout << "(" << p.first << ", " << p.second << ") ";
        }
        cout << endl;
        cout << "Length: " << result.size() - 1 << endl;
        cout << "Start: (" << start_row << ", " << start_col << ")" << endl;
        cout << "End: (" << end_row << ", " << end_col << ")" << endl;
    }
    return 0;
}
