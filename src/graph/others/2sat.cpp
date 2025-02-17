// Tested
// 1-indexed, a xor b = (a or b) and (¬a or ¬b)
int getIdx(int x) { return abs(x) << 1 | (x < 0); }
void addEdge(Graph<int> &G, int u, int v) {
    u = getIdx(u), v = getIdx(v);
    G.addEdge(u ^ 1, v); G.addEdge(v ^ 1, u);
}
bool avaiable(Graph<int> &G) {
    SCC scc(G);
    int N = G.size() - 2 >> 1;
    for(int i = 1; i <= N; ++i) {
        if(scc.scc_id[i << 1] == scc.scc_id[i << 1 | 1]) return false;
    }
    return true;
}