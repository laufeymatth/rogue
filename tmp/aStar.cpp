#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <functional>

using namespace std;

// Node class representing a point on the grid
class Node {
public:
    int x, y;
    double g_score, f_score;
    Node *parent;
    Node(int x, int y, double g_score, double f_score, Node *parent = nullptr) {
        this->x = x;
        this->y = y;
        this->g_score = g_score;
        this->f_score = f_score;
        this->parent = parent;
    }
};

// Helper function to calculate the Euclidean distance between two nodes
double heuristic(Node *a, Node *b) {
    return sqrt(pow(a->x - b->x, 2) + pow(a->y - b->y, 2));
}

// Helper function to get the neighbors of a given node
vector<Node*> get_neighbors(vector<vector<char>>& matrix, Node *node, int size) {
    vector<Node*> neighbors;

    int x = node->x;
    int y = node->y;

    // Check left neighbor
    if (x > 0 && matrix[x-1][y] != '#') {
        neighbors.push_back(new Node(x-1, y, 0, 0, nullptr));
    }

    // Check right neighbor
    if (x < size-1 && matrix[x+1][y] != '#') {
        neighbors.push_back(new Node(x+1, y, 0, 0, nullptr));
    }

    // Check top neighbor
    if (y > 0 && matrix[x][y-1] != '#') {
        neighbors.push_back(new Node(x, y-1, 0, 0, nullptr));
    }

    // Check bottom neighbor
    if (y < size-1 && matrix[x][y+1] != '#') {
        neighbors.push_back(new Node(x, y+1, 0, 0, nullptr));
    }

    return neighbors;
}



// A* algorithm function
vector<Node*> a_star(vector<vector<char>>& matrix, Node *start, Node *end, int size) {
    vector<Node*> open_set, closed_set, path;
    open_set.push_back(start);

    while (!open_set.empty()) {
        Node *current = open_set[0];
        int current_index = 0;
        for (int i = 1; i < open_set.size(); i++) {
            if (open_set[i]->f_score < current->f_score) {
                current = open_set[i];
                current_index = i;
            }
        }

        if (current->x == end->x && current->y == end->y) {
            Node *node = current;
            while (node != nullptr) {
                path.push_back(node);
                node = node->parent;
            }
            reverse(path.begin(), path.end());
            break;
        }

        open_set.erase(open_set.begin() + current_index);
        closed_set.push_back(current);

        vector<Node*> neighbors = get_neighbors(matrix, current, size);
        for (Node *neighbor : neighbors) {
            bool in_closed_set = false;
            for (Node *closed_node : closed_set) {
                if (neighbor->x == closed_node->x && neighbor->y == closed_node->y) {
                    in_closed_set = true;
                    break;
                }
            }
            if (in_closed_set) {
                continue;
            }

            double tentative_g_score = current->g_score + 1.0;

            bool in_open_set = false;
            for (Node *open_node : open_set) {
                if (neighbor->x == open_node->x && neighbor->y == open_node->y) {
                    in_open_set = true;
                    break;
                }
            }

            if (!in_open_set || tentative_g_score < neighbor->g_score) {
                neighbor->parent = current;
                neighbor->g_score = tentative_g_score;
                neighbor->f_score = neighbor->g_score + heuristic(neighbor, end);

                if (!in_open_set) {
                    open_set.push_back(neighbor);
                }
            }
        }
    }

    return path;
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
    Node *start = new Node(0, 0, 0, 0, nullptr);
    Node *end = new Node(5, 5, 0, 0, nullptr);

    // Find the path using A*
    vector<Node*> path = a_star(matrix, start, end, size);

    // Print the path
    for (Node *node : path) {
        cout << "(" << node->x << ", " << node->y << ")" << endl;
    }

    return 0;
}
