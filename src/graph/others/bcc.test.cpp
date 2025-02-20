// 11400, 11266
#include<bits/stdc++.h>

using namespace std;

template<typename T> struct Graph {
    vector<vector<T>> G;
    Graph(int N) { G.resize(N + 1); }
    void addEdge(int u, T data) { G[u].emplace_back(data); }
    int size() { return (int)G.size() - 1; }
    vector<T>& operator[](const int &idx) { return G[idx]; }
};

struct BCC {
    int N, dfs_id;
    Graph<int> G;
    vector<int> dfsn;
    vector<vector<pair<int, int>>> bcc;
    stack<pair<int, int>> S;
    BCC(Graph<int> _G):G(_G) { 
        N = G.size();
        dfsn.resize(N + 1);
        dfs_id = 0;
        for(int i = 1; i <= N; ++i) {
            if(dfsn[i] == 0) dfs(i, 0);
        }
    }
    
    int dfs(int cur, int prev) {
        int res = dfsn[cur] = ++ dfs_id;
        for(int nxt: G[cur]) {
            if(nxt == prev) continue;
            if(dfsn[cur] > dfsn[nxt]) S.emplace(cur, nxt);
            if(dfsn[nxt] > 0) res = min(res, dfsn[nxt]);
            else {
                int tmp = dfs(nxt, cur);
                res = min(res, tmp);
                if(tmp >= dfsn[cur]) {
                    vector<pair<int, int>> curBCC;
                    while(!S.empty() && S.top() != make_pair(cur, nxt)) {
                        curBCC.push_back(S.top());
                        S.pop();
                    }
                    curBCC.push_back(S.top());
                    S.pop();
                    bcc.push_back(curBCC);
                }
            }
        }
        return res;
    }
    vector<int> cut_vertex() {
        vector<int> cnt(N + 1), last(N + 1, -1);
        for(int i = 0; i < (int)bcc.size(); ++i) {
            for(auto [u, v]: bcc[i]) {
                if(last[u] < i) ++ cnt[u], last[u] = i;
                if(last[v] < i) ++ cnt[v], last[v] = i;
            }
        }
        vector<int> vertex;
        for(int i = 1; i <= N; ++i) {
            if(cnt[i] > 1) vertex.push_back(i);
        }
        return vertex;
    }
    vector<pair<int, int>> cut_edge() {
        vector<pair<int, int>> edges;
        for(int i = 0; i < (int)bcc.size(); ++i) {
            if(bcc[i].size() > 1) continue;
            auto [u, v] = bcc[i][0];
            edges.emplace_back(min(u, v), max(u, v));
        }
        return edges;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M; cin >> N >> M;
    Graph<int> G(N);
    for(int i = 0; i < M; ++i) {
        int u, v; cin >> u >> v;
        G.addEdge(u, v);
        G.addEdge(v, u);
    }
    BCC bcc(G);
    vector<int> answer = bcc.cut_vertex();
    cout << answer.size() << '\n';
    for(int x: answer) cout << x << ' ';
    // vector<pair<int, int>> edges = bcc.cut_edge();
    // sort(edges.begin(), edges.end());
    // cout << edges.size() << '\n';
    // for(auto [u, v]: edges) cout << u << ' ' << v << '\n';

    return 0;
}