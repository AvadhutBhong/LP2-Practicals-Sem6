#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int vertices) {
        V = vertices;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected
    }

    void printAdjacencyList() {
        cout << "Adjacency List:\n";
        for (int i = 0; i < V; i++) {
            cout << i << ": ";
            for (int neighbor : adj[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    void DFS_Recursive_FromNode(int start) {
        vector<bool> visited(V, false);
        cout << "DFS (Recursive) starting from node " << start << ": ";
        dfsRecursiveUtil(start, visited);
        cout << endl << endl;
    }

private:
    void dfsRecursiveUtil(int node, vector<bool>& visited) {
        visited[node] = true;
        cout << node << " ";

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfsRecursiveUtil(neighbor, visited);
            }
        }
    }

public:
    void BFS_Recursive_FromNode(int start) {
        vector<bool> visited(V, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;

        cout << "BFS (Recursive) starting from node " << start << ": ";
        bfsRecursiveUtil(q, visited);
        cout << endl << endl;
    }

private:
    void bfsRecursiveUtil(queue<int>& q, vector<bool>& visited) {
        if (q.empty())
            return;

        int node = q.front();
        q.pop();
        cout << node << " ";

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }

        bfsRecursiveUtil(q, visited);
    }
};

int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    Graph g(V);

    cout << "Enter " << E << " edges (u v) [0-based indexing]:\n";
    for (int i = 0; i < E; i++) {
        int u, v;
        cout << "Enter Edge " << i + 1 << " (u v): ";
        cin >> u >> v;

        if (u < 0 || u >= V || v < 0 || v >= V) {
            cout << "Invalid vertices! Enter between 0 and " << V - 1 << ". Try again.\n";
            i--; // retry
            continue;
        }

        g.addEdge(u, v);
    }

    int choice, startNode;

    do {
        cout << "\n--- Graph Traversal Menu (Recursive Only) ---\n";
        cout << "1. Print Adjacency List\n";
        cout << "2. DFS (Recursive) from Start Node\n";
        cout << "3. BFS (Recursive) from Start Node\n";
        cout << "4. Exit\n";
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        if (choice >= 2 && choice <= 3) {
            cout << "Enter start node: ";
            cin >> startNode;

            if (startNode < 0 || startNode >= V) {
                cout << "Invalid start node! Please enter between 0 and " << V - 1 << ".\n";
                continue;
            }
        }

        switch (choice) {
            case 1:
                g.printAdjacencyList();
                break;
            case 2:
                g.DFS_Recursive_FromNode(startNode);
                break;
            case 3:
                g.BFS_Recursive_FromNode(startNode);
                break;
            case 4:
                cout << "Exiting. Thank you!\n";
                break;
            default:
                cout << "Invalid choice! Please enter 1-4.\n";
        }
    } while (choice != 4);

    return 0;
}
