// Tested
// 1-indexed, Need Graph template
// O(V+E)
struct SCC {
    int N, id;
    Graph<int> G;
    vector<int> D, scc_id;
    vector<vector<int>> scc;
    stack<int> st;

    SCC(const Graph<int> &_G):G(_G) {
        id = 0;
        N = G.size();
        D.resize(N + 1);
        scc_id.resize(N + 1, -1);
        for(int i = 1; i <= N; ++i) if(!D[i]) dfs(i);
    }
    int dfs(int cur) {
        D[cur] = ++id;
        st.push(cur);
        int par = D[cur];
        for(const auto &nxt: G[cur]) {
            if(!D[nxt]) par = min(par, dfs(nxt));
            else if(scc_id[nxt] == -1) par = min(par, D[nxt]);
        }
        if(par == D[cur]) {
            scc.emplace_back();
            while(!st.empty()) {
                int x = st.top(); st.pop();
                scc_id[x] = (int)scc.size() - 1;
                scc.back().push_back(x);
                if(x == cur) break;
            }
        }
        return par;
    }
    int size() { return scc.size(); }
    vector<int> &operator[] (const int idx) { return scc[idx]; }
    Graph<int> graph() {
        int K = size();
        Graph<int> sccG(K);
        for(int i = 1; i <= N; ++i) {
            for(const int &nxt: G[i]) {
                if(scc_id[i] == scc_id[nxt]) continue;
                sccG.addEdge(scc_id[i], scc_id[nxt]);
            }
        }
        for(int i = 0; i < K; ++i) {
            sort(sccG[i].begin(), sccG[i].end());
            sccG[i].erase(unique(sccG[i].begin(), sccG[i].end()), sccG[i].end());
        }
        return sccG;
    }
};