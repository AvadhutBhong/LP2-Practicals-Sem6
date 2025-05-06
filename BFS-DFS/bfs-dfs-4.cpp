#include <iostream>
#include <vector>
#include <queue>
#include <stack>
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

    void dfsRecursiveUtil(int node, vector<bool>& visited) {
        visited[node] = true;
        cout << node << " ";

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfsRecursiveUtil(neighbor, visited);
            }
        }
    }

    void DFS_Iterative_FromNode(int start) {
        vector<bool> visited(V, false);
        stack<int> st;
        st.push(start);
        visited[start] = true;
        cout << "DFS (Iterative) starting from node " << start << ": ";

        while (!st.empty()) {
            int node = st.top();
            st.pop();
            cout << node << " ";

            for (auto it = adj[node].rbegin(); it != adj[node].rend(); ++it) {
                if (!visited[*it]) {
                    visited[*it] = true;
                    st.push(*it);
                }
            }
        }
        cout << endl << endl;
    }

    void BFS_Iterative_FromNode(int start) {
        vector<bool> visited(V, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;

        cout << "BFS (Iterative) starting from node " << start << ": ";

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl << endl;
    }

    void BFS_Recursive_FromNode(int start) {
        vector<bool> visited(V, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;

        cout << "BFS (Recursive) starting from node " << start << ": ";
        bfsRecursiveUtil(q, visited);
        cout << endl << endl;
    }

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
        cout << "\n--- Graph Traversal Menu ---\n";
        cout << "1. Print Adjacency List\n";
        cout << "2. DFS (Recursive) from Start Node\n";
        cout << "3. DFS (Iterative) from Start Node\n";
        cout << "4. BFS (Iterative) from Start Node\n";
        cout << "5. BFS (Recursive) from Start Node\n";
        cout << "6. Exit\n";
        cout << "Enter your choice (1-6): ";
        cin >> choice;

        if (choice >= 2 && choice <= 5) {
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
                g.DFS_Iterative_FromNode(startNode);
                break;
            case 4:
                g.BFS_Iterative_FromNode(startNode);
                break;
            case 5:
                g.BFS_Recursive_FromNode(startNode);
                break;
            case 6:
                cout << "Exiting. Thank you!\n";
                break;
            default:
                cout << "Invalid choice! Please enter 1-6.\n";
        }
    } while (choice != 6);

    return 0;
}



