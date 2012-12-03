#include <iostream>
#include <vector>
using namespace std;

// フローがpreflowであるとは:
//    各頂点において、入ってくるフローの合計 >= 出ていくフローの合計が満たされている
// 頂点の属性hがhight functitonであるとは: 
//    残余グラフ上の各エッジ(u,v)に関して、h(u) <= h(v) + 1 が満たされている
//
// push/relabelできなくなった時
//    - preflowは満たされている
//    - hight functionは満たされている
//    - overflowing vertexは無い (あればpush/relabelどちらかできる)
//      - つまり現在のpreflowは正しくflowである
//    - 残余グラフにs->tへのパスは無い

const int INF = (int)1e9;

struct Edge {
    int capacity;
};

struct Vertex {
    int excess;
    int height;
    vector<Edge> edges;
};

vector<Vertex> G;

void push(int u, int v) {
    // Applies when: u is overflowing, c(u,v) > 0, and u.h = v.h + 1
    // Action: push max flow from u to v
}

void relabel(Vertex& u) {
    // Applies when: u is overflowing and all v is not downhill from u
    // Action: Increase the hight of u
    int min_h = INF;
    for (int i = 0; i < u.edges.size(); i++)
        if (u.edges[i].capacity > 0)
            min_h = min(min_h, u.
        
    u.height = min_h + 1;
}

int main() {

}
