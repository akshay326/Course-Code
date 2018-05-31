#include "graph_algorithms.h"

# define INF 10000000

Graph::Graph(int V) {
    this->V = V;
    this->E = 0; // No Edges by default
}

DisjointSets::DisjointSets(int n) {
    // Allocate memory
    this->n = n;
    parent = new int[n + 1];
    rnk = new int[n + 1];

    // Initially, all vertices are in
    // different sets and have rank 0.
    for (int i = 0; i <= n; i++) {
        rnk[i] = 0;

        //every element is parent of itself
        parent[i] = i;
    }
}

void Graph::addEdge(int u, int v, int w) {
    edges.push_back({w, {u, v}});
}

// Prints shortest paths from src to all other vertices
void Graph::primMST() {
    // Create a priority queue to store vertices that
    // are being preinMST. This is weird syntax in C++.
    // Refer below link for details of this syntax
    // http://geeksquiz.com/implement-min-heap-using-stl/
    priority_queue<iPair, vector<iPair>, greater<iPair> > pq;

    int src = 0; // Taking vertex 0 as source

    // Create a vector for keys and initialize all
    // keys as infinite (INF)
    vector<int> key(V, INF);

    // To store parent array which in turn store MST
    vector<int> parent(V, -1);

    // To keep track of vertices included in MST
    vector<bool> inMST(V, false);

    // Insert source itself in priority queue and initialize
    // its key as 0.
    pq.push(make_pair(0, src));
    key[src] = 0;

    /* Looping till priority queue becomes empty */
    while (!pq.empty()) {
        // The first vertex in pair is the minimum key
        // vertex, extract it from priority queue.
        // vertex label is stored in second of pair (it
        // has to be done this way to keep the vertices
        // sorted key (key must be first item in pair)
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true;  // Include vertex in MST

        for (auto &edge : edges)
            if (edge.second.first == u){
            // Get vertex label and weight of current adjacent
            // of u.
            int v = edge.second.second;
            int weight = edge.first;

            //  If v is not in MST and weight of (u,v) is smaller
            // than current key of v
            if (inMST[v] == false ) {
                // Updating key of v
                key[v] = weight;
                pq.push(make_pair(key[v], v));
                parent[v] = u;
            }
        }
    }

    // Print edges of MST using parent array
    for (int i = 1; i < V; ++i)
        printf("%d - %d\n", parent[i], i);
}


void Graph::kruskalMST() {
    // Sort edges in increasing order on basis of cost
    sort(edges.begin(), edges.end());

    // Create disjoint sets
    DisjointSets ds(V);

    // Iterate through all sorted edges
    for (auto &edge : edges) {
        int u = edge.second.first;
        int v = edge.second.second;

        int set_u = ds.find(u);
        int set_v = ds.find(v);

        // Check if the edge is creating a cycle
        if (set_u != set_v) {
            // Current edge will be in the MST so print it
            cout << u << " - " << v << endl;

            // Merge two sets
            ds.merge(set_u, set_v);
        }
    }
}