// 11408
#include<bits/stdc++.h>

using namespace std;

template<typename T>
struct MinCostMaxFlow {
    struct Edge {
        int edge_id, node_idx, cost, flow, rev;
        T dist;
        Edge(int _edge_id, int _node_idx, int _cost, T _dist, int _rev):edge_id(_edge_id),node_idx(_node_idx),cost(_cost),flow(0),dist(_dist),rev(_rev) { }
        int spare() { return cost - flow; }
    };

    vector<Edge> edges;
    vector<vector<int>> G;
    vector<pair<int, int>> par;
    vector<T> dist;

    int src, snk, N;
    T INF;

    MinCostMaxFlow(int _N) { 
        src = _N + 1;
        snk = src + 1;
        N = snk;

        INF = numeric_limits<T>::max();

        G.resize(N + 1);
        par.resize(N + 1, make_pair(-1, -1));
    }
    bool spfa(int s, int e) {
        vector<int> InQ(N + 1);
        dist = vector<T>(N + 1, INF);

        dist[s] = 0;
        deque<int> dq; dq.push_back(s);
        InQ[s] = 1;

        while(!dq.empty()) {
            int cur = dq.front(); dq.pop_front();
            InQ[cur] = 0;
            for(const int &x: G[cur]) {
                Edge &e = edges[x];
                if(e.spare() > 0 && dist[e.node_idx] > dist[cur] + e.dist) {
                    dist[e.node_idx] = dist[cur] + e.dist;
                    par[e.node_idx] = make_pair(cur, e.edge_id);
                    if(InQ[e.node_idx] == 0) {
                        dq.push_back(e.node_idx);
                        InQ[e.node_idx] = 1;
                    }
                }
            }
        }
        return dist[e] != INF;
    }

    // min_cost, max_flow
    pair<T, int> flow_after_spfa(int s, int e) {
        int mn = numeric_limits<int>::max();
        for(int cur = e; cur != s; cur = par[cur].first) {
            mn = min(mn, edges[par[cur].second].spare());
        }
        if(mn == 0) return make_pair<T, int>(-1, -1);
        T min_cost = 0;
        int max_flow = mn;
        for(int cur = e; cur != s; cur = par[cur].first) {
            min_cost += (T)mn * edges[par[cur].second].dist;
            edges[par[cur].second].flow += mn;
            edges[edges[par[cur].second].rev].flow -= mn;
        }
        return make_pair(min_cost, max_flow);
    }
    pair<T, int> flow(int s, int e) {
        pair<T, int> ret;
        while (spfa(s, e)) {
            pair<T, int> cur = flow_after_spfa(s, e);
            if (cur.first == -1) break;
            ret.first += cur.first;
            ret.second += cur.second;
        }
        return ret;
    }

    // addEdge
    void addEdge(int u, int v, int cost, T dist) {
        int a = edges.size();
        int b = a + 1;

        Edge uv = Edge(a, v, cost, dist, b);
        Edge vu = Edge(b, u, 0, -dist, a);

        edges.push_back(uv);
        edges.push_back(vu);

        G[u].push_back(a);
        G[v].push_back(b);
    }

    pair<T, int> flow() { return flow(src, snk); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M; cin >> N >> M;
    MinCostMaxFlow<int> flow(801);
    for(int i = 1; i <= N; ++i) {
        int K; cin >> K;
        for(int j = 0; j < K; ++j) {
            int u, v; cin >> u >> v;
            flow.addEdge(i, 400 + u, 1, v);
        }
    }
    for(int i = 1; i <= N; ++i) flow.addEdge(flow.src, i, 1, 0);
    for(int i = 1; i <= M; ++i) flow.addEdge(400 + i, flow.snk, 1, 0);
    auto [ans1, ans2] = flow.flow();
    cout << ans2 << '\n' << ans1 << '\n';
    return 0;
}
