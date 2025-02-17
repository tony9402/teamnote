// Tested
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