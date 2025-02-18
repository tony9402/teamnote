// 13510
#include<bits/stdc++.h>

using namespace std;

template<typename T> struct Graph {
    vector<vector<T>> G;
    Graph(int N) { G.resize(N + 1); }
    void addEdge(int u, T data) { G[u].emplace_back(data); }
    int size() { return (int)G.size(); }
    vector<T>& operator[](const int &idx) { return G[idx]; }
};

template<typename T>
struct Segment {
    vector<T> tree;
    int siz;

    Segment(int N = 1 << 17) {
        for(siz = 1; siz < N; siz <<= 1);
        tree = vector<T>(siz << 1);
    }
    void update(int idx, T data) {
        tree[idx += siz] = data;
        while(idx >>= 1) tree[idx] = merge(tree[idx << 1], tree[idx << 1 | 1]);
    }
    T query(int l, int r) {
        T lret = T(), rret = T();
        for(l += siz, r += siz; l <= r; l >>= 1, r >>= 1) {
            if(l & 1) lret = merge(lret, tree[l ++]);
            if(~r & 1) rret = merge(tree[r --], rret);
        }
        return merge(lret, rret);
    }
    T merge(T, T);
};

struct HLD {
    Graph<int> G;
    vector<int> par, top, dep, siz, in, out;
    Segment<int> seg;
    int id;
    HLD(Graph<int> G):G(G) {
        int N = (int)G.size();
        siz = par = top = dep = in = out = vector<int>(N);
        seg = Segment<int>(N);
        id = 0;
    }
    void dfs(int cur=1, int prev=0) {
        siz[cur] = 1;
        par[cur] = prev;
        dep[cur] = dep[prev] + 1;
        for(int &nxt : G[cur]) {
            if(nxt == prev) continue;
            dfs(nxt, cur);
            siz[cur] += siz[nxt];
            if(siz[nxt] > siz[G[cur][0]]) swap(nxt, G[cur][0]);
        }
    }
    void dfs2(int cur=1, int prev=0) {
        in[cur] = ++id;
        if(cur == 1) top[cur] = 1;
        for(int nxt: G[cur]) {
            if(nxt == prev)continue;
            top[nxt] = (nxt == G[cur][0] ? top[cur] : nxt);
            dfs2(nxt, cur);
        }
        out[cur] = id;
    }
    int lca(int a, int b) {
        while(top[a] != top[b]) {
            if(dep[top[a]] < dep[top[b]]) swap(a, b);
            a = par[top[a]];
        }
        if(in[a] > in[b]) swap(a, b);
        return a;
    }
    void update(int, int);
    int query(int, int);
};

template<typename T> T Segment<T>::merge(T a, T b) { return max<T>(a, b); }

void HLD::update(int a, int b) {
    seg.update(a, b);
}

int HLD::query(int s, int e) {
    int ret = 0;
    while(top[s] != top[e]) {
        if(dep[top[s]] < dep[top[e]]) swap(s, e);
        ret = max(ret, seg.query(in[top[s]], in[s]));
        s = par[top[s]];
    }
    if(in[s] > in[e]) swap(s, e);
    return max(ret, seg.query(in[s] + 1, in[e]));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N; cin >> N;
    Graph<int> G(N+1);
    vector<tuple<int,int,int>> edges;
    for(int i = 1; i < N; ++i) {
        int u, v, w; cin >> u >> v >> w;
        G.addEdge(u, v); G.addEdge(v, u);
        edges.emplace_back(u, v, w);
    }
    HLD hld(G);
    hld.dfs(); hld.dfs2();
    for(auto &[u, v, w] : edges) {
        if(hld.dep[u] < hld.dep[v]) swap(u, v);
        hld.update(hld.in[u], w);
    }
    int Q; cin >> Q;
    for(int i = 0; i < Q; ++i) {
        int cmd, a, b; cin >> cmd >> a >> b;
        if(cmd == 1) {
            auto &[u, v, w] = edges[a - 1];
            hld.update(hld.in[u], w = b);
        }
        else cout << hld.query(a, b) << '\n';
    }

    return 0;
}