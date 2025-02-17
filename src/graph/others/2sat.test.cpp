// 3747
#include<bits/stdc++.h>

using namespace std;

template<typename T> struct Graph {
    vector<vector<T>> G;
    Graph(int N) { G.resize(N + 1); }
    void addEdge(int u, T data) { G[u].emplace_back(data); }
    int size() { return (int)G.size() - 1; }
    vector<T>& operator[](const int &idx) { return G[idx]; }
};

// 1-indexed, Need Graph template
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

// 1-indexed
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M;
    while(cin >> N >> M) {
        Graph<int> G(2 * N + 2);
        for(int i = 0; i < M; ++i) {
            int u, v; cin >> u >> v;
            addEdge(G, u, v);
        }
        cout << avaiable(G) << '\n';
    }

    return 0;
}

