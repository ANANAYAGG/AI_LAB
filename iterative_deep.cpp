#include <iostream>
#include <stack>
using namespace std;

#define MAX_NODES 21

void DFSWithDepth(int graph[MAX_NODES][MAX_NODES], int numNodes, int startNode, int depth) {
    bool visited[MAX_NODES] = {false};
    stack<pair<int, int>> s;
    s.push(make_pair(startNode, depth));
    
    cout << "DFS Traversal Order with Depth " << depth << ": ";
    
    while (!s.empty()) {
        int node = s.top().first;
        int currentDepth = s.top().second;
        s.pop();
        
        if (!visited[node]) {
            visited[node] = true;
            cout << node << " ";
            
            if (currentDepth > 1) { // Explore deeper only if depth is greater than 1
                for (int i = numNodes - 1; i >= 0; --i) { // Check neighbors
                    if (graph[node][i] == 1 && !visited[i]) {
                        s.push(make_pair(i, currentDepth - 1));
                    }
                }
            }
        }
    }
    cout << endl;
}

int main() {
    int graph[MAX_NODES][MAX_NODES] = {
        {0, 1, 0, 0, 1, 0},
        {1, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0, 0},
        {0, 0, 1, 0, 1, 1},
        {1, 0, 0, 1, 0, 1},
        {0, 0, 0, 1, 1, 0}
    };

    int numNodes = 6; // Number of nodes in the graph
    int startNode = 0; // Starting node for traversal
    
    for (int depth = 1; depth <= 3; ++depth) {
        DFSWithDepth(graph, numNodes, startNode, depth);
    }
    
    return 0;
}
