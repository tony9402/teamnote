// 13511
#include<bits/stdc++.h>

using namespace std;
using ll = long long;

template<typename T> struct Graph {
    vector<vector<T>> G;
    Graph(int N) { G.resize(N + 1); }
    void addEdge(int u, T data) { G[u].emplace_back(data); }
    int size() { return (int)G.size() - 1; }
    vector<T>& operator[](const int &idx) { return G[idx]; }
};

// 1-index, dist (ll), Need Graph Template
struct LCA {
    int N, sz;
    Graph<pair<int, int>> G;
    vector<int> dep;
    vector<ll> dist;
    vector<vector<int>> par;
    LCA(const Graph<pair<int, int>> &_G):G(_G) {
        for(sz = 1; (1 << sz) < N; ++ sz);
        N = G.size();
        dep = vector<int>(N + 1);
        dist = vector<ll>(N + 1);
        par = vector<vector<int>>(sz, vector<int>(N + 1));
        dfs(1, 0);
        for(int j = 1; j < sz; ++j) for(int i = 1; i <= N; ++i) par[j][i] = par[j - 1][par[j - 1][i]];
    }
    void dfs(int cur, int prev) {
        dep[cur] = dep[prev] + 1;
        for(const auto &[nxt, w]: G[cur]) {
            if(nxt == prev) continue;
            par[0][nxt] = cur;
            dist[nxt] = dist[cur] + w;
            dfs(nxt, cur);
        }
    }
    int lca(int u, int v) {
        if(dep[u] > dep[v]) swap(u, v);
        for(int i = sz - 1; ~i; --i) if(dep[u] <= dep[par[i][v]]) v = par[i][v];
        if(u == v) return u;
        for(int i = sz - 1; ~i; --i) if(par[i][u] != par[i][v]) u = par[i][u], v = par[i][v];
        return par[0][u];
    }
    ll distance(int u, int v) { return dist[u] + dist[v] - 2 * dist[lca(u, v)]; }
    int kth(int u, int v, int k) {
        int l = lca(u, v), dif = dep[u] - dep[l] + 1;
        if(dif < k) k = dep[v] - dep[l] + dif - k, u = v, v = l;
        else --k;
        for(int i = sz - 1; ~i; --i) if(k & (1 << i)) u = par[i][u];
        return u;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N; cin >> N;
    Graph<pair<int, int>> G(N);
    for(int i = 1; i < N; ++i) {
        int u, v, w; cin >> u >> v >> w;
        G.addEdge(u, {v, w}); G.addEdge(v, {u, w});
    }
    LCA lca(G);
    int Q; cin >> Q;
    while(~--Q) {
        int cmd, u, v, k; cin >> cmd >> u >> v;
        if(cmd == 1) cout << lca.distance(u, v) << '\n';
        else cin >> k, cout << lca.kth(u, v, k) << '\n';
    }

    return 0;
}