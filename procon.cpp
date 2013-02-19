#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

//===============================================================//
//                        Number theory
//===============================================================//

///////////////////////////////////////////////////////////////////
// 拡張ユークリッドの互除法
// a, b (a > b)の最大公約数を求めると同時に、
// ax + by = gcd(a,b)を満たすx, yのペアを求める
int extgcd(int a, int b, int& x, int& y) {
    int d = a;
    if (b != 0) {
        d = extgcd(b, a % b, y, x);
        y -= (a / b) * x;
    } else {
        x = 1; y = 0;
    }
    return d;
}

///////////////////////////////////////////////////////////////////
// エラトステネスのふるい
// n以下の素数のリストを返す
vector<int> getPrimes(int n) {
    vector<int> is_prime(n + 1, true);
    vector<int> res;
    for (int i=2; i<=n; i++) if (is_prime[i]) {
        res.push_back(i);
        for (int j=i*2; j<=n; j+=i) is_prime[j] = false;
    }
    return res;
}

///////////////////////////////////////////////////////////////////
// 素数判定
bool isPrime(int n) {
    for (int i=2; i*i<=n; i++) if (n%i == 0) return false;
    return n != 1;
}

///////////////////////////////////////////////////////////////////
// 素因数分解
map<int, int> factorize(int n) {
    map<int, int> res;
    for (int i = 2; i*i <= n; i++)
        while (n % i == 0) { res[i]++; n /= i; }
    if (n != 1) res[n] = 1;
    return res;
}

///////////////////////////////////////////////////////////////////
//// 合同式の値用クラス
struct mint {
    static const int n = 1000000007;
    int v;
    mint() : v(0) {}
    mint(int v) : v(v) {}
    mint& operator+= (const mint& o) {v = (v+o.v)%n; return *this;}
    mint& operator-= (const mint& o) {v = (v-o.v+n)%n; return *this;}
    mint& operator*= (const mint& o) {v = ((long long)v*o.v)%n; return *this;}
    mint& operator/= (const mint& o) {v = (o.inv()*=v).v; return *this;}
    mint inv() const {return (*this).pow(n-2);}
    mint pow(int e) const {mint r=1,x=v; while(e){if(e&1)r*=x; x*=x; e>>=1;} return r;}
};
mint operator+(const mint& x, const mint& y) {return (x.v+y.v)%mint::n;}
mint operator-(const mint& x, const mint& y) {return (x.v-y.v+mint::n)%mint::n;}
mint operator*(const mint& x, const mint& y) {return ((long long)x.v*y.v)%mint::n;}
mint operator/(const mint& x, const mint& y) {return x*y.inv();}
std::ostream& operator<<(std::ostream& os, const mint& x) {return os<<x.v;}

//===============================================================//
//                        Combinatrics
//===============================================================//

//===============================================================//
//                        Data structures
//===============================================================//

///////////////////////////////////////////////////////////////////
// Union-Find Tree
struct UnionFind {
    UnionFind(int n) {
        p = rank = vector<int>(n, 0);
        for (int i=0; i<n; i++) p[i] = i;
    }
    int find(int x) { return x==p[x] ? p[x] : p[x]=find(p[x]); }
    bool same(int x, int y) { return find(x) == find(y); }
    void unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return;
        if (rank[rx] >= rank[ry]) p[ry] = rx; else p[rx] = ry;
        if (rank[rx] == rank[ry]) rank[rx]++;
    }
    int size() {
        int res = 0;
        for (int i=0; i<p.size(); i++) if (p[i] == i) res++;
        return res;
    }
    vector<int> p, rank;
};

///////////////////////////////////////////////////////////////////
// Binary Indexed Tree
struct BIT {
    vector<long long> bit;
    BIT(int n) { bit = vector<long long>(n+1); }
    long long sum(int i) {
        long long res = 0;
        while (i > 0) { res += bit[i]; i -= (i & -i); }
        return res;
    }
    long long sum(int i, int j) { return sum(j) - sum(i-1); }
    void add(int i, long long x) {
        while (i < bit.size()) { bit[i] += x; i += (i & -i); }
    }
};

///////////////////////////////////////////////////////////////////
// Meldable Heap
//  (confirmed at http://utpc2012.contest.atcoder.jp/tasks/utpc2012_12)
template<class T> class SkewHeap {
  public:
    SkewHeap() : root(NULL), sz(0) {}
    bool empty()            { return root == NULL; }
    T top()                 { return root->val; }
    void push(T val)        { root = meld(root, new Node(val)); sz++; }
    void pop()              { Node* old = root; root = meld(root->l, root->r); delete old; sz--; }
    void meld(SkewHeap& a)  { root = meld(root, a.root); sz += a.size(); }
    int size()              { return sz; }
  private:
    struct Node {
        Node *l, *r;
        T val;
        Node(T val) : l(NULL), r(NULL), val(val) {}
    };
    Node* root;
    int sz;
    Node* meld(Node* a, Node* b) {
        if (a == NULL) return b;
        if (b == NULL) return a;
        if (a->val < b->val) swap(a, b);
        a->r = meld(a->r, b);
        swap(a->l, a->r);
        return a;
    }
};

///////////////////////////////////////////////////////////////////
// Meldable Median Heap
//  (confirmed at http://utpc2012.contest.atcoder.jp/tasks/utpc2012_12)
template<class T> class MedianHeap {
  public:
    bool empty() { return small.empty(); }
    T median() { return small.top(); }
    void push(T val) {
        if (small.size() == large.size()) small.push(val); else large.push(-val);
        maintain();
    }
    void pop() { small.pop(); maintain(); }
    void meld(MedianHeap& a) { small.meld(a.small); large.meld(a.large); maintain(); }
  private:
    SkewHeap<T> small, large;
    void maintain() {
        while (small.size() > large.size()+1) {
            large.push(-small.top());
            small.pop();
        }
        while (small.size() < large.size()) {
            small.push(-large.top());
            large.pop();
        }
        while (!small.empty() && !large.empty() && small.top() > -large.top()) {
            T s = small.top(), l = large.top();
            small.pop(); large.pop();
            small.push(-l); large.push(-s);
        }
    }
};

//===============================================================//
//                        Graph
//===============================================================//

///////////////////////////////////////////////////////////////////
// 二部グラフ
class BipartGraph {
public:
    BipartGraph(int n) {
        G = vector<vector<int> >(n);
        match = vector<int>(n);
        used = vector<bool>(n);
    }
    void addEdge(int u, int v) {
        G[u].push_back(v);
        G[v].push_back(u);
    }
    int maxMatch() {
        fill(match.begin(), match.end(), -1);
        int res = 0;
        for (int i=0; i<G.size(); i++) {
            if (match[i] < 0) {
                fill(used.begin(), used.end(), false);
                if (dfs(i)) res++;
            }
        }
        return res;
    }
private:
    vector<vector<int> > G;
    vector<int> match;
    vector<bool> used;
    bool dfs(int v) {
        used[v] = true;
        for (int i=0; i<G[v].size(); i++) {
            int u = G[v][i];
            if (match[u] < 0 || (!used[match[u]] && dfs(match[u]))) {
                match[v] = u;
                match[u] = v;
                return true;
            }
        }
        return false;
    }
};

///////////////////////////////////////////////////////////////////
// 最大フロー
class Dinic {
public:
    Dinic(int nElement) {
        m_edges = vector< vector<Edge> >(nElement);
        m_level = vector<int>(nElement);
        m_iter = vector<int>(nElement);
    }
    void addEdge(int from, int to, int cap) {
        m_edges[from].push_back(Edge(to, cap, m_edges[to].size()));
        m_edges[to].push_back(Edge(from, 0, m_edges[from].size()-1));
    }
    int maxFlow(int s, int t) {
        int flow = 0;
        for (;;) {
            bfs(s);
            if (m_level[t] < 0) break;
            fill(m_iter.begin(), m_iter.end(), 0);
            int f = 0;
            while ((f = dfs(s, t, INF)) > 0) {
                flow += f;
            }
        }
        return flow;
    }
private:
    struct Edge {
        int to, cap, rev;
        Edge(int t, int c, int r):to(t),cap(c),rev(r){}
    };
    static const int INF = 1000000000;
    vector< vector<Edge> > m_edges;
    vector<int> m_level;
    vector<int> m_iter;
    void bfs(int s) {
        fill(m_level.begin(), m_level.end(), -1);
        m_level[s] = 0;
        queue<int> que;
        que.push(s);
        while (que.size() > 0) {
            int v = que.front(); que.pop();
            for (int i = 0; i < m_edges[v].size(); i++) {
                Edge& e = m_edges[v][i];
                if (e.cap > 0 && m_level[e.to] == -1) {
                    m_level[e.to] = m_level[v] + 1;
                    que.push(e.to);
                }
            }
        }
    }
    int dfs(int v, int t, int f) {
        if (v == t) return f;
        for (int& i = m_iter[v]; i < m_edges[v].size(); i++) {
            Edge& e = m_edges[v][i];
            if (e.cap > 0 && m_level[e.to] > m_level[v]) {
                int d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    m_edges[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
};

///////////////////////////////////////////////////////////////////
// 最小コストフロー
class MinCostFlowGraph {
public:
    MinCostFlowGraph(int n) : INF(100000000) {
        G = vector<vector<edge> >(n);
        h = vector<int>(n);
        dist = vector<int>(n);
        prevv = vector<int>(n);
        preve = vector<int>(n);
    }
    void add_edge(int from, int to, int cap, int cost) {
        G[from].push_back(edge(to, cap, cost, G[to].size()));
        G[to].push_back(edge(from, 0, -cost, G[from].size()-1));
    }
    int min_cost_flow(int s, int t, int f) {
        int res = 0;
        fill(h.begin(), h.end(), 0);
        while (f > 0) {
            priority_queue<PII, vector<PII>, greater<PII> > que;
            fill(dist.begin(), dist.end(), INF);
            dist[s] = 0;
            que.push(PII(0, s));
            while (!que.empty()) {
                PII p = que.top(); que.pop();
                int v = p.second;
                if (dist[v] >= p.first) {
                    for (int i = 0; i < G[v].size(); i++) {
                        edge& e = G[v][i];
                        if (e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
                            dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
                            prevv[e.to] = v;
                            preve[e.to] = i;
                            que.push(PII(dist[e.to], e.to));
                        }
                    }
                }
            }
            if (dist[t] == INF) return -1;
            for (int v = 0; v < h.size(); v++) h[v] += dist[v];
            int d = f;
            for (int v = t; v != s; v = prevv[v]) d = min(d, G[prevv[v]][preve[v]].cap);
            f -= d;
            res += d * h[t];
            for (int v = t; v != s; v = prevv[v]) {
                edge& e = G[prevv[v]][preve[v]];
                e.cap -= d;
                G[v][e.rev].cap += d;
            }
        }
        return res;
    }
private:
    const int INF;
    typedef pair<int, int> PII;
    struct edge {
        int to, cap, cost, rev;
        edge(int t, int ca, int co, int r):to(t),cap(ca),cost(co),rev(r){}
    };
    vector<vector<edge> > G;
    vector<int> h, dist, prevv, preve;
};


//===============================================================//
//                        String
//===============================================================//

///////////////////////////////////////////////////////////////////
// KMP法によって文字列TからパターンPにマッチするshiftの数をかぞえる
//  (confirmed at SRM 433 Div1 250)
int count_by_KMP(const string& T, const string& P) {
    // compute prefix funtion
    int m = P.length();
    vector<int> p(m+1);
    p[1] = 0;
    int k = 0;
    for (int q = 2; q <= m; q++) {
        while (k > 0 && P[k] != P[q-1]) k = p[k];
        if (P[k] == P[q-1]) k = k+1;
        p[q] = k;
    }
    // pattern match
    int matches = 0;
    int q = 0;
    for (int i = 0; i < T.size(); i++) {
        while (q > 0 && P[q] != T[i]) q = p[q];
        if (P[q] == T[i]) q = q+1;
        if (q == m) {
            matches++;
            q = p[q];
        }
    }
    return matches;
}


//===============================================================//
//                        Test code
//===============================================================//
int main() {
    BipartGraph bg(10);
    bg.addEdge(0, 5); bg.addEdge(1, 5);
    cerr << bg.maxMatch() << endl;
    
    UnionFind uf(10);
    uf.unite(0, 1); uf.unite(1, 9); uf.unite(1, 5); uf.unite(2, 8);
    cerr << uf.same(1, 8) << endl;
    cerr << uf.same(5, 9) << endl;
    cerr << uf.size() << endl;

    mint a = 0;
    a += 3; a *= 3; a -= 2*a;
    cerr << a << endl;

    map<int,int> m = factorize(40);
    for (map<int,int>::iterator itr = m.begin(); itr != m.end(); itr++)
        cerr << itr->first << "^" << itr->second << " ";
    cerr << endl;
}
