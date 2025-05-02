#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Structure for edge representation (destination vertex, weight of the edge)
struct Edge {
    int to;
    int weight;
};

// Function to implement Prim's algorithm and find the Minimum Spanning Tree (MST)
void primMST(int V, vector<vector<Edge>>& adj) {
    vector<int> dist(V, INT_MAX);  // Stores minimum distance to each vertex
    vector<int> parent(V, -1);     // Stores parent of each vertex in MST
    vector<bool> visited(V, false); // Marks vertices as visited or not

    // Min-heap priority queue for selecting the minimum weight edge
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Start with the first vertex (0)
    dist[0] = 0;
    pq.push({0, 0});  // {distance, vertex}

    while (!pq.empty()) {
        int u = pq.top().second;  // Get the vertex with the minimum distance
        pq.pop();

        // If vertex 'u' is already visited, skip it
        if (visited[u]) continue;

        visited[u] = true;  // Mark vertex 'u' as visited

        // Iterate over all adjacent vertices of 'u'
        for (const Edge& edge : adj[u]) {
            int v = edge.to;
            int weight = edge.weight;

            // If the vertex 'v' is not visited and the weight of edge u-v is less than the current dist[v], update dist[v]
            if (!visited[v] && weight < dist[v]) {
                dist[v] = weight;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    // Print the MST edges and total weight
    int totalWeight = 0;
    cout << "\n✅ Minimum Spanning Tree (MST):\n";
    cout << "Edge\tWeight\n";
    for (int v = 1; v < V; v++) {
        cout << parent[v] << " - " << v << "\t" << dist[v] << "\n";
        totalWeight += dist[v];
    }
    cout << "\n🌐 Total Weight of MST: " << totalWeight << "\n";
}

int main() {
    int V, E;
    cout << "Enter the number of vertices (0 to V-1): ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    vector<vector<Edge>> adj(V);

    cout << "\nEnter " << E << " edges in format (u v weight):\n";
    for (int i = 1; i <= E; i++) {
        int u, v, w;
        cout << "Edge " << i << ": ";
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // For undirected graph
    }

    primMST(V, adj);

    return 0;
}

/*
Sample Input:
Enter the number of vertices (0 to V-1): 5
Enter the number of edges: 6

Enter 6 edges in format (u v weight):
Edge 1: 0 1 2
Edge 2: 0 3 6
Edge 3: 1 2 3
Edge 4: 1 3 8
Edge 5: 1 4 5
Edge 6: 2 4 7

Expected Output:

✅ Minimum Spanning Tree (MST):
Edge    Weight
0 - 1   2
1 - 2   3
0 - 3   6
1 - 4   5

🌐 Total Weight of MST: 16
*/
