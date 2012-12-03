#include <iostream>
#include <vector>
using namespace std;

struct Edge {
    int from, to, cap, rev;
    Edge(int from, int to, int cap, int rev)
        : from(from), to(to), cap(cap), rev(rev) {}
};
const int INF = 100000;
const int V = 6;
vector<Edge> G[V];
bool used[V];

void add_edge(int from, int to, int cap) {
    G[from].push_back(Edge(from, to, cap, G[to].size()));
    G[to].push_back(Edge(to, from, 0, G[from].size()-1));
}

int find_augmenting_path(int v, int sink, int flow) {
    if (v == sink) return flow;
    used[v] = true;
    for (int i = 0; i < G[v].size(); i++) {
        Edge& e = G[v][i];
        if (!used[e.to] && e.cap > 0) {
            int d = find_augmenting_path(e.to, sink, min(flow, e.cap));
            if (d != 0) {
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int augment(int source, int sink, int flow) {
    memset(used, 0, sizeof(used));
    return find_augmenting_path(source, sink, INF);
}

int ford_fulkerson(int source, int sink) {
    int max_flow = 0;
    while (int f = augment(source, sink, INF)) {
        max_flow += f;
        cout << "+ " << f << endl;
    }
    return max_flow;
}

int main() {
    add_edge(0, 1, 16);
    add_edge(0, 2, 13);
    add_edge(1, 3, 12);
    add_edge(2, 1, 4);
    add_edge(2, 4, 14);
    add_edge(3, 2, 9);
    add_edge(3, 5, 20);
    add_edge(4, 3, 7);
    add_edge(4, 5, 4);

    int flow = ford_fulkerson(0, 5);
    cout << flow << endl;
}
