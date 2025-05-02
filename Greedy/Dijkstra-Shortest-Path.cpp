#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Edge {
    int to;
    int weight;
};

void dijkstra(int V, vector<vector<Edge>>& adj, int src) {
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    // Min-heap priority queue {distance, node}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        int currDist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // Skip stale entry
        if (currDist > dist[u]) continue;

        for (const Edge& edge : adj[u]) {
            int v = edge.to;
            int weight = edge.weight;

            if (dist[v] > currDist + weight) {
                dist[v] = currDist + weight;
                pq.push({dist[v], v});
            }
        }
    }

    // Print shortest distances
    cout << "\nShortest distances from Source Vertex " << src << ":\n";
    cout << "Vertex\tDistance\n";
    for (int i = 0; i < V; i++) {
        cout << i << "\t" << dist[i] << endl;
    }
}

int main() {
    int V, E;
    cout << "Enter number of vertices (numbered from 0 to V-1): ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    vector<vector<Edge>> adj(V);

    cout << "Enter edges in format: u v weight (vertices numbered 0 to " << V-1 << ")\n";
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cout << "Enter edge " << i + 1 << ": ";
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // For undirected graph
    }

    int src;
    cout << "Enter source vertex (0 to " << V-1 << "): ";
    cin >> src;

    dijkstra(V, adj, src);

    return 0;
}

/*
Sample Input:
Enter number of vertices (numbered from 0 to V-1): 5
Enter number of edges: 6
Enter edges in format: u v weight (vertices numbered 0 to 4)
Enter edge 1: 0 1 2
Enter edge 2: 0 3 6
Enter edge 3: 1 2 3
Enter edge 4: 1 3 8
Enter edge 5: 1 4 5
Enter edge 6: 2 4 7
Enter source vertex (0 to 4): 0

Expected Output:
Shortest distances from Source Vertex 0:
Vertex  Distance
0       0
1       2
2       5
3       6
4       7
*/
