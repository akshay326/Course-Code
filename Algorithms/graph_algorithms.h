#ifndef ALGORITHMS_GRAPH_ALGORITHMS_H
#define ALGORITHMS_GRAPH_ALGORITHMS_H

#include <bits/stdc++.h>
typedef std::pair<int, int> iPair;
using namespace std;

class DisjointSets {
    int *parent, *rnk;
    int n;

public:
    // Constructor.
    explicit DisjointSets(int n);

    // Find the parent of a node 'u'
    // Path Compression
    int find(int u) {
        /* Make the parent of the nodes in the path
           from u--> parent[u] point to parent[u] */
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }

    // Union by rank
    void merge(int x, int y) {
        x = find(x), y = find(y);

        /* Make tree with smaller height
           a subtree of the other tree  */
        if (rnk[x] > rnk[y])
            parent[y] = x;
        else // If rnk[x] <= rnk[y]
            parent[x] = y;

        if (rnk[x] == rnk[y])
            rnk[y]++;
    }
};

class Graph {
    int V, E;    // No. of vertices

    // In a weighted graph, we need to store vertex
    // and weight pair for every edge
    vector< pair<int, iPair> > edges;

public:
    explicit Graph(int V);  // Constructor

    // function to add an edge to graph
    void addEdge(int u, int v, int w);

    // Print MST using Prim's algorithm
    void primMST();

    // Print MST using Kruskal's algorithm
    void kruskalMST();
};

/*
 *     int V = 9;
    Graph g(V);

    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);

    g.primMST();

//    g.kruskalMST();
 */

#endif //ALGORITHMS_GRAPH_ALGORITHMS_H
