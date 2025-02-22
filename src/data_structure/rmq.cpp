// Tested
// Need Graph Template 1-indexed
// build O(NlogN), query O(1) RMQ
template<typename T> struct RMQ {
    vector<int> L;
    vector<vector<T>> table;
    RMQ() { }
    RMQ(const vector<T> &V) {
        int N = (int)V.size() - 1;
        L = vector<int>(N + 1);
        for(int i = 2; i <= N; ++i) L[i] = L[i / 2] + 1;
        table = vector<vector<T>>(L[N] + 1, vector<T>(N + 1));
        for(int i = 1; i <= N; ++i) table[0][i] = V[i];
        for(int i = 1; i <= L[N]; ++i) {
            int k = 1 << (i - 1);
            for(int j = 1; j + k <= N; ++j) {
                table[i][j] = merge(table[i - 1][j], table[i - 1][j + k]);
            }
        }
    }
    T query(int l, int r) {
        int d = L[r - l + 1];
        return merge(table[d][l], table[d][r - (1 << d) + 1]);
    }
    T merge(T a, T b) { return min(a, b); }
};
// build O(NlogN), query O(1) LCA
// 1-indexed
struct LCA {
    Graph<int> G;
    RMQ<pair<int, int>> rmq;
    vector<int> in, dep;
    LCA(Graph<int> _G):G(_G) { 
        int id = 0;
        int N = G.size();
        in = dep = vector<int>(N + 1);
        vector<pair<int, int>> V(1);
        function<void(int, int)> dfs = [&](int cur, int prev) -> void {
            in[cur] = ++id;
            dep[cur] = dep[prev] + 1;
            V.emplace_back(dep[cur], cur);
            for(int nxt: G[cur]) {
                if(nxt == prev) continue;
                dfs(nxt, cur);
                V.emplace_back(dep[cur], cur);
                ++ id;
            }
        };
        dfs(1, 0);
        rmq = RMQ<pair<int, int>>(V);
    }
    int lca(int u, int v) {
        if(in[u] > in[v]) swap(u, v);
        return rmq.query(in[u], in[v]).second;
    }
};