// Tested
vector<int> par(N);
int ans = 0;
for (int i = 1; i < N; ++i) {
    Dinic dinic(N);
    for (auto [u, v]: edges) dinic.addEdge(u, v, 1, false);
    int src = i, snk = par[i];
    int flow = dinic.flow(src, snk);
    ans = max(ans, flow);
    for (int j = i + 1; j < N; ++j) {
        if (dinic.level[j] != -1 && par[j] == par[i]) par[j] = i;
    }
}