#include <iostream>
 #include <queue>
 #include <stack>
 using namespace std;
 const int MAX_NODES = 10;
 void BFS(int graph[MAX_NODES][MAX_NODES], int numNodes, int startNode)
 {
    bool visited[MAX_NODES] = {false};
    queue<int> q;
    visited[startNode] = true;
    q.push(startNode);
    cout << "BFS Traversal Order: ";
    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        cout << node << " ";
        for (int i = 0; i < numNodes; ++i)
        {
            if (graph[node][i] == 1 && !visited[i])
            {
                visited[i] = true;
                q.push(i);
            }
        }
    }
    cout << endl;
 }
 void DFS(int graph[MAX_NODES][MAX_NODES], int numNodes, int startNode)
 {
    bool visited[MAX_NODES] = {false};
    stack<int> s;
    s.push(startNode);
    cout << "DFS Traversal Order: ";
    while (!s.empty())
    {
        int node = s.top();
        s.pop();
        if (!visited[node])
        {
            visited[node] = true;
            cout << node << " ";
            for (int i = numNodes - 1; i >= 0; --i)
            {
                if (graph[node][i] == 1 && !visited[i])
                {
                    s.push(i);
                }
            }
        }
    }
    cout << endl;
 }
 int main()
 {
    int graph[MAX_NODES][MAX_NODES] = {
        {0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, 
        {1, 0, 0, 1, 1, 0, 0, 0, 0, 0}, 
        {1, 0, 0, 0, 0, 1, 0, 0, 0, 0}, 
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 1, 0, 0, 0, 0, 1, 1, 0, 0}, 
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    int numNodes = 8;
    int startNode;
    cout << "Enter the starting node (0 to " << numNodes - 1 << "): ";
    cin >> startNode;
    int choice;
    cout << "Choose traversal method:\n1. BFS\n2. DFS\nEnter choice (1 or 2): ";
    cin >> choice;
    if (choice == 1)
    {
        BFS(graph, numNodes, startNode);
    }
    else if (choice == 2)
    {
        DFS(graph, numNodes, startNode);
    }
    else
    {
        cout << "Invalid choice!" << endl;
    }
    return 0;
 }
