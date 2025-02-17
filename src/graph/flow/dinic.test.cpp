// 11377
#include<bits/stdc++.h>

using namespace std;

struct Dinic {
    struct Node {
        int node_idx, cost, flow, rev;
        Node(int _nxt = -1, int _cost = 0, int _rev = -1):node_idx(_nxt),cost(_cost),flow(0),rev(_rev) { }
        int spare() { return cost - flow; }
        void setRev(int _rev) { rev = _rev; }
    };
    vector<Node> nodes;
    vector<vector<int>> G;
    vector<int> level;
    vector<int> work;

    int src, snk, asrc, asnk, N;
    Dinic(int _N) {
        src = _N + 1;
        snk = src + 1;
        asrc = snk + 1;
        asnk = asrc + 1;
        N = asnk;
        G.resize(N + 1);
    }
    bool bfs(int s, int e) {
        level = vector<int>(N + 1, -1);
        level[s] = 0;
        queue<int> Q; Q.push(s);
        while(!Q.empty()) {
            int cur = Q.front(); Q.pop();
            for(const int &x: G[cur]) {
                Node &nxt = nodes[x];
                if(nxt.spare() > 0 && level[nxt.node_idx] == -1) {
                    level[nxt.node_idx] = level[cur] + 1;
                    Q.push(nxt.node_idx);
                }
            }
        }
        return ~level[e];
    }
    int dfs(int s, int e, int f) {
        if(s == e) return f;
        for(int &i = work[s]; i < (int)G[s].size(); ++i) {
            Node &nxt = nodes[G[s][i]];
            if(nxt.spare() > 0 && level[nxt.node_idx] == level[s] + 1) {
                int ret = dfs(nxt.node_idx, e, min(f, nxt.spare()));
                if(ret > 0) {
                    nxt.flow += ret;
                    nodes[nxt.rev].flow -= ret;
                    return ret;
                }
            }
        }
        return 0;
    }
    int flow(int s, int e) {
        int ret = 0;
        while(bfs(s, e)) {
            work = vector<int>(N + 1, 0);
            while(true) {
                int x = dfs(s, e, numeric_limits<int>::max());
                if(x == 0) break;
                ret += x;
            }
        }
        return ret;
    }
    void addEdge(int u, int v, int cost, bool is_directed = true, bool is_unique = false) {
        if(is_unique) {
            for(const int &x: G[u]) {
                if(nodes[x].node_idx == v) {
                    nodes[x].cost += cost;
                    if(!is_directed) return;
                    break;
                }
            }
            if(!is_directed) {
                for(const int &x: G[v]) {
                    if(nodes[x].node_idx == u) {
                        nodes[x].cost += cost;
                        return;
                    }
                }
            }
        }
        int a = (int)nodes.size(), b = a + 1;
        Node uv = Node(v, cost, b);
        Node vu = Node(u, is_directed ? 0 : cost, a);
        nodes.push_back(uv); nodes.push_back(vu);
        G[u].push_back(a); G[v].push_back(b);
    }
    void addLREdge(int u, int v, int lower, int upper) {
        if(lower) {
            addEdge(asrc, v, lower);
            addEdge(u, asnk, lower);
        }
        addEdge(u, v, upper - lower);
    }
    int flow() { return flow(src, snk); }
    int lrflow() { return flow(asrc, asnk); }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    Dinic flow(2000);
    int N, M, K; cin >> N >> M >> K;
    flow.addEdge(flow.src, flow.asrc, K);
    for(int i = 0; i < N; ++i) {
        int w; cin >> w;
        for(int j = 0; j < w; ++j) {
            int c; cin >> c;
            flow.addEdge(i, c + 999, 1);
        }
        flow.addEdge(flow.src, i, 1);
        flow.addEdge(flow.asrc, i, 1);
    }
    for(int i = 0; i < M; ++i) flow.addEdge(i + 1000, flow.snk, 1);
    cout << flow.flow(flow.src, flow.snk);

    return 0;
}
