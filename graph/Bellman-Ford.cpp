#include <iostream>
#include <vector>
using namespace std;

const int INF = (int)1e9;
const int NIL = -1;

// vertices
const int NUM_V = 7;
int d[NUM_V];
int p[NUM_V];

// edges
struct Edge {
    int from, to, cost;
    Edge(int f, int t, int c) : from(f), to(t), cost(c) {}
};
vector<Edge> edges;

void initialize(int s) {
    for (int v = 0; v < NUM_V; v++) {
        d[v] = INF;
        p[v] = NIL;
    }
    d[s] = 0;
}

void relax(int u, int v, int w) {
    if (d[v] > d[u] + w) {
        d[v] = d[u] + w;
        p[v] = u;
    }
}

bool bellman_ford(int s) {
    initialize(s);
    for (int k = 0; k < NUM_V-1; k++)
        for (int i = 0; i < edges.size(); i++)
            relax(edges[i].from, edges[i].to, edges[i].cost);
    for (int i = 0; i < edges.size(); i++)
        if (d[edges[i].to] > d[edges[i].from] + edges[i].cost)
            return false;
    return true;
}

int main() {
    for (int i = 1; i <= 6; i++)
        edges.push_back(Edge(0, i, 0));
    edges.push_back(Edge(2, 1, 1));
    edges.push_back(Edge(4, 1, -4));
    edges.push_back(Edge(3, 2, 2));
    edges.push_back(Edge(5, 2, 7));
    edges.push_back(Edge(6, 2, 5));
    edges.push_back(Edge(6, 3, 10));
    edges.push_back(Edge(2, 4, 2));
    edges.push_back(Edge(1, 5, -1));
    edges.push_back(Edge(4, 5, 3));
    edges.push_back(Edge(3, 6, -8));

    bool ok = bellman_ford(0);

    if (ok) {
        for (int i = 1; i <= 6; i++)
            cout << d[i] << " ";
    } else {
        cout << "containing negative cycle";
    }
    cout << endl;
}
