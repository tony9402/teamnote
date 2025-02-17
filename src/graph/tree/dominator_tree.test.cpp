// 19335
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M;
    cin >> N >> M;
    vector<vector<pair<int, ll>>> G(N);
    vector<tuple<int, int, int>> edges;
    for (int i = 0; i < M; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        G[--u].emplace_back(--v, w);
        G[v].emplace_back(u, w);
        edges.emplace_back(u, v, w);
    }

    priority_queue<pair<ll, int>> pq;
    const ll INF = LLONG_MAX / 2;
    vector<ll> dist(N, INF);
    pq.emplace(dist[0] = 0, 0);
    while (!pq.empty()) {
        auto [d, cur] = pq.top();
        pq.pop();
        if (dist[cur] != -d) continue;
        for (auto [nxt, w] : G[cur]) {
            if (dist[nxt] > dist[cur] + w) {
                dist[nxt] = dist[cur] + w;
                pq.emplace(-dist[nxt], nxt);
            }
        }
    }

    vector<vector<int>> dag(N);
    for (auto &[u, v, w] : edges) {
        if (dist[u] > dist[v]) swap(u, v);
        if (dist[u] + w == dist[v]) dag[u].push_back(v);
    }

    vector<int> idom = DominatorTree(dag, 0);
    vector<vector<int>> tree(N);
    for (int i = 1; i < N; ++i) tree[idom[i]].push_back(i);
    vector<int> sz(N);
    function<int(int)> dfs = [&](int cur) -> int {
        sz[cur] = 1;
        for (int nxt : tree[cur]) sz[cur] += dfs(nxt);
        return sz[cur];
    };
    dfs(0);

    for (const auto &[u, v, w] : edges) {
        if (u != idom[v]) cout << 0 << '\n';
        else cout << sz[v] << '\n';
    }

    return 0;
}