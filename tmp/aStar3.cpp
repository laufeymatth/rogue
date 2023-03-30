#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

// Node class representing a point on the grid
class Node {
public:
    int x, y;
    int distance;
    bool visited;
    Node* prev; // added for tracking the previous node in the path

    Node(int x, int y, int distance = numeric_limits<int>::max(), bool visited = false) {
        this->x = x;
        this->y = y;
        this->distance = distance;
        this->visited = visited;
        this->prev = nullptr;
    }
};

// Helper function to get the neighbors of a given node
vector<Node*> get_neighbors(vector<vector<char>>& matrix, Node *node, int size) {
    vector<Node*> neighbors;

    int x = node->x;
    int y = node->y;

    // Check left neighbor
    if (x > 0 && matrix[x-1][y] != '#') {
        neighbors.push_back(new Node(x-1, y));
    }

    // Check right neighbor
    if (x < size-1 && matrix[x+1][y] != '#') {
        neighbors.push_back(new Node(x+1, y));
    }

    // Check top neighbor
    if (y > 0 && matrix[x][y-1] != '#') {
        neighbors.push_back(new Node(x, y-1));
    }

    // Check bottom neighbor
    if (y < size-1 && matrix[x][y+1] != '#') {
        neighbors.push_back(new Node(x, y+1));
    }

    return neighbors;
}

// Dijkstra's algorithm function
vector<Node*> dijkstra(vector<vector<char>>& matrix, Node *start, Node *end, int size) {
    // Initialize the priority queue
    auto cmp = [](Node* a, Node* b) { return a->distance > b->distance; };
    priority_queue<Node*, vector<Node*>, decltype(cmp)> pq(cmp);

    // Set the start node's distance to 0
    start->distance = 0;
    pq.push(start);

    while (!pq.empty()) {
        // Get the node with the smallest distance
        Node *current = pq.top();
        pq.pop();

        // Stop if the end node is reached
        if (current->x == end->x && current->y == end->y) {
            vector<Node*> path;
            while (current != nullptr) {
                path.push_back(current);
                current = current->prev;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        // Skip if the node has already been visited
        if (current->visited) {
            continue;
        }
        current->visited = true;

        // Get the neighbors of the current node
        vector<Node*> neighbors = get_neighbors(matrix, current, size);

        // Update the distances of the neighbors
        for (Node *neighbor : neighbors) {
            int distance = current->distance + 1;
            if (distance < neighbor->distance) {
                neighbor->distance = distance;
                neighbor->prev = current; // track the previous node in the path
                pq.push(neighbor);
            }
        }
    }

    // No path found
    return {};
}

int main() {
    // Define the matrix
    vector<vector<char>> matrix = {
        {'.', '.', '#', '.', '.', '.'},
        {'.', '.', '#', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.'},
        {'.', '#', '.', '.', '.', '.'},
        {'.', '#', '.', '.', '#', '.'},
        {'.', '#', '.', '.', '.', '.'}
    };
    int size = 6;

    // Define the start and end nodes
    Node *start = new Node(0, 0);
    Node *end = new Node(size-1, size-1);

    // Find the path using Dijkstra's algorithm
    vector<Node*> path = dijkstra(matrix, start, end, size);

    // Print the path
    cout << "Shortest path from (" << start->x << ", " << start->y << ") to (" << end->x << ", " << end->y << "): ";
    for (Node *node : path) {
        cout << "(" << node->x << ", " << node->y << ") ";
    }
    cout << endl;

    // Free memory
    delete start;
    delete end;
    for (Node *node : path) {
        delete node;
    }

    return 0;
}