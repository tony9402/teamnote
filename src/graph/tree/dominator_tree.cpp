// Tested
vector<int> DominatorTree(const vector<vector<int>> &G, int start_node) {
    int N = (int)G.size();
    vector<vector<int>> rG(N);
    for (int cur = 0; cur < N; ++cur) {
        for (int nxt : G[cur]) rG[nxt].push_back(cur);
    }

    vector<int> uf(N), sdom_id(N), idom(N, -1), sdom(N, -1);
    for (int i = 0; i < N; ++i) uf[i] = sdom_id[i] = i;
    function<int(int)> find = [&](int x) -> int {
        if (uf[x] == x) return x;
        int tmp = find(uf[x]);
        if (sdom[sdom_id[x]] > sdom[sdom_id[uf[x]]]) sdom_id[x] = sdom_id[uf[x]];
        return uf[x] = tmp;
    };
    vector<int> numbering, par(N);
    function<void(int)> dfs = [&](int cur) -> void {
        sdom[cur] = numbering.size();
        numbering.push_back(cur);
        for (int nxt : G[cur]) {
            if (sdom[nxt] != -1) continue;
            par[nxt] = cur;
            dfs(nxt);
        }
    };
    dfs(start_node);
    int K = (int)numbering.size();
    vector<vector<int>> buf(N);
    vector<int> final_uf(N);
    for (int i = K - 1; i >= 0; --i) {
        int u = numbering[i];
        if (sdom[u] == -1) continue;
        for (int v : rG[u]) {
            if (sdom[v] == -1) continue;
            find(v);
            if (sdom[u] > sdom[sdom_id[v]]) sdom[u] = sdom[sdom_id[v]];
        }
        buf[numbering[sdom[u]]].push_back(u);
        for (int nxt : buf[par[u]]) {
            find(nxt);
            final_uf[nxt] = sdom_id[nxt];
        }
        buf[par[u]].clear();
        uf[u] = par[u];
    }
    idom[start_node] = start_node;
    for (const int &x : numbering) {
        if (sdom[x] == sdom[final_uf[x]]) idom[x] = sdom[x];
        else idom[x] = idom[final_uf[x]];
    }
    for (const int &x : numbering) {
        if (x != start_node) idom[x] = numbering[idom[x]];
    }
    return idom;
}