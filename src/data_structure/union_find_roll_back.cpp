// Tested
struct UnionFind {
    vector<int> par, rank;
    stack<tuple<int, int, int>> st;
    UnionFind(int N) { 
        par = rank = vector<int>(N + 1); 
        iota(par.begin(), par.end(), 0);
    }

    int find(int x) { return par[x] == x ? x : find(par[x]); }
    bool merge(int u, int v) {
        u = find(u); v = find(v);
        if(u == v) return false;
        if(rank[u] < rank[v]) swap(u, v);
        par[v] = u;
        st.emplace(u, v, rank[u] == rank[v]);
        if(rank[u] == rank[v]) ++rank[u];
        return true;
    }
    void revert(int cnt) {
        while(cnt --> 0) {
            auto [u, v, c] = st.top(); st.pop();
            par[v] = v;
            if(c) -- rank[u];
        }
    }
    int conn(int u, int v) { return find(u) == find(v); }
};