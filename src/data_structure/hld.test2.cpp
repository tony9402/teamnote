// 11438
#include<bits/stdc++.h>

using namespace std;

template<typename T> struct Graph {
    vector<vector<T>> G;
    Graph(int N) { G.resize(N + 1); }
    void addEdge(int u, T data) { G[u].emplace_back(data); }
    int size() { return (int)G.size(); }
    vector<T>& operator[](const int &idx) { return G[idx]; }
};

struct HLD {
    Graph<int> G;
    vector<int> par, top, dep, siz, in, out;
    int id;
    HLD(Graph<int> G):G(G) {
        int N = (int)G.size();
        siz = par = top = dep = in = out = vector<int>(N);
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N; cin >> N;
    Graph<int> G(N+1);
    for(int i = 1; i < N; ++i) {
        int u, v; cin >> u >> v;
        G.addEdge(u, v); G.addEdge(v, u);
    }
    HLD hld(G);
    hld.dfs(); hld.dfs2();
    int Q; cin >> Q;
    while(~--Q) {
        int u, v; cin >> u >> v;
        cout << hld.lca(u,v) << '\n';
    }

    return 0;
}