#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// Function to construct adjacency 
vector<vector<vector<int>>> constructAdj(vector<vector<int>> 
                             &edges, int V) {
                                 
    // adj[u] = list of {v, wt}
    vector<vector<vector<int>>> adj(V); 

    for (const auto &edge : edges) {
        int u = edge[0];
        int v = edge[1];
        int wt = edge[2];
        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt}); 
    }
    
    return adj;}

// Returns shortest distances from src to all other vertices
vector<int> dijkstra(int V, vector<vector<int>> &edges, int src){
    
    // Create adjacency list
    vector<vector<vector<int>>> adj = constructAdj(edges, V);

    // Create a priority queue to store vertices that
    // are being preprocessed.
    priority_queue<vector<int>, vector<vector<int>>, 
                   greater<vector<int>>> pq;

    // Create a vector for distances and initialize all
    // distances as infinite
    vector<int> dist(V, INT_MAX);

    // Insert source itself in priority queue and initialize
    // its distance as 0.
    pq.push({0, src});
    dist[src] = 0;

    // Looping till priority queue becomes empty (or all
    // distances are not finalized) 
    while (!pq.empty()){
        
        // The first vertex in pair is the minimum distance
        // vertex, extract it from priority queue.
        int u = pq.top()[1];
        pq.pop();

        // Get all adjacent of u.
        for (auto x : adj[u]){
            
            // Get vertex label and weight of current
            // adjacent of u.
            int v = x[0];
            int weight = x[1];

            // If there is shorter path to v through u.
            if (dist[v] > dist[u] + weight)
            {
                // Updating distance of v
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

// Driver program to test methods of graph class
int main(){
int V, E, src; 
cin >> V >> E >> src;

if (V <= 0 || E < 0 || src < 0 || src >= V) {
    cerr << "Invalid input\n";
    return 1;
}

vector<vector<int>> edges;

for (int i = 0; i < E; ++i) {
    int u, v, w;
    cin >> u >> v >> w;

    if (u < 0 || u >= V || v < 0 || v >= V) {
        cerr << "Invalid edge\n";
        return 1;
    }

    if (w < 0) {
        cerr << "Negative weights not allowed in Dijkstra\n";
        return 1;
    }

    edges.push_back({u, v, w});
}

    vector<int> result = dijkstra(V, edges, src);

    // Print shortest distances in one line
    for (int dist : result)
        cout << dist << " ";
 
    return 0;
}
