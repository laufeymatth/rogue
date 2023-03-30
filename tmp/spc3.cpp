#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point
{
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

// Returns the Euclidean distance between two points.
double distance(Point a, Point b)
{
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

// Returns a vector of all the neighboring points that are within range of the given point.
vector<Point> getNeighbors(vector<vector<char>> &grid, int rows, int cols, Point p, int range)
{
    vector<Point> neighbors;
    if (p.x > 0 && grid[p.x-1][p.y] == '.' )//&& distance(p, Point(p.x-1, p.y)) <= range)
        neighbors.push_back(Point(p.x-1, p.y));
    if (p.x < rows-1 && grid[p.x+1][p.y] == '.' )//&& distance(p, Point(p.x+1, p.y)) <= range)
        neighbors.push_back(Point(p.x+1, p.y));
    if (p.y > 0 && grid[p.x][p.y-1] == '.' )//&& distance(p, Point(p.x, p.y-1)) <= range)
        neighbors.push_back(Point(p.x, p.y-1));
    if (p.y < cols-1 && grid[p.x][p.y+1] == '.' )//&& distance(p, Point(p.x, p.y+1)) <= range)
        neighbors.push_back(Point(p.x, p.y+1));
    return neighbors;
}

// Finds the shortest path between two points in a graph using Dijkstra's algorithm.
vector<Point> dijkstra(vector<vector<char>> &grid, int rows, int cols, Point start, Point end, int range)
{
    // Convert the grid into a graph.
    vector<vector<pair<int, int>>> graph(rows * cols);
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            if (grid[r][c] == '.')
            {
                int u = r * cols + c;
                vector<Point> neighbors = getNeighbors(grid, rows, cols, Point(r, c), range);
                for (Point neighbor : neighbors)
                {
                    int v = neighbor.x * cols + neighbor.y;
                    double dist = distance(Point(r, c), neighbor);
                    graph[u].push_back({dist, v});
                }
            }
        }
    }

    // Initialize distance vector and priority queue.
    vector<double> distance(rows * cols, INT_MAX);
    vector<int> prev(rows * cols, -1);
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;

    // Add the starting vertex to the queue.
    int startIdx = start.x * cols + start.y;
    distance[startIdx] = 0;
    pq.push({0, startIdx});

    // Run Dijkstra's algorithm.
    while (!pq.empty())
    {
        // Get the vertex with the smallest distance.
        int u = pq.top().second;
        pq.pop();

        // If we have reached the destination, return the path.
        if (u == end.x * cols + end.y)
        {
            vector<Point> path;
            while (u != startIdx)
            {
                path.push_back({u / cols, u % cols});
                u = prev[u];
            }
            path.push_back({u / cols, u % cols});
            reverse(path.begin(), path.end());
            return path;
        }

        // Update the distances of the neighbors.
        if (distance[u] != INT_MAX)
        {
            for (auto &edge : graph[u])
            {
                double dist = edge.first;
                int v = edge.second;
                double alt = distance[u] + dist;
                if (alt < distance[v])
                {
                    distance[v] = alt;
                    prev[v] = u;
                    pq.push(make_pair(distance[v], v));
                }
            }
        }
    }

    // No path was found.
    return {};
}

int main()
{
    int rows = 5;
    int cols = 5;
    Point start(0, 0);
    Point end(4, 0);
    int range = 2;

    vector<vector<char>> grid = {
        {'.', '.', '.', '#', '.'},
        {'#', '#', '.', '#', '.'},
        {'.', '.', '.', '#', '.'},
        {'.', '#', '.', '#', '.'},
        {'.', '.', '.', '.', '.'}};

    vector<Point> path = dijkstra(grid, rows, cols, start, end, range);

    // Print the path.
    for (Point p : path)
    {
        cout << "(" << p.x << ", " << p.y << ") -> ";
    }
    cout << endl;

    return 0;
}