// 16911
#include<bits/stdc++.h>

using namespace std;

// Roll-back Union Find
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M; cin >> N >> M;

    map<pair<int, int>, int> mp;
    vector<int> used(M + 1), C(M + 1);
    vector<pair<int, int>> Queries(M + 1);
    vector<pair<int, int>> Q(M + 1);
    vector<tuple<int, int, int, int>> V;

    for(int i = 1; i <= M; ++i) {
        int cmd, u, v; cin >> cmd >> u >> v;
        if(u > v) swap(u, v);

        if(cmd == 1) {
            used[i] = 1;
            mp[make_pair(u, v)] = i;
            Queries[i] = make_pair(u, v);
        }
        else if(cmd == 2) {
            auto it = mp[make_pair(u, v)];
            used[it] = 0;
            V.emplace_back(u, v, C[it] + 1, C[i - 1]);
        }
        else if(cmd == 3) {
            Q[C[i - 1] + 1] = make_pair(u, v);
            C[i] = 1;
        }
        C[i] += C[i - 1];
    }

    for(int i = 1; i <= M; ++i) {
        if(used[i]) {
            auto [u, v] = Queries[i];
            V.emplace_back(u, v, C[i] + 1, C[M]);
        }
    }

    UnionFind uf(M + 1);

    int siz;
    for(siz = 1; siz < M; siz <<= 1);
    vector<vector<pair<int, int>>> G(siz << 1);
    function<void(int, int, int, int, int, pair<int, int>)> update = [&](int l, int r, int s, int e, int pos, pair<int, int> data) -> void {
        if(s <= l && r <= e) return G[pos].emplace_back(data), (void)0;
        if(e < l || r < s) return;
        int mid = (l + r) / 2;
        update(l, mid, s, e, pos << 1, data);
        update(mid + 1, r, s, e, pos << 1 | 1, data);
    };
    function<void(int, int, int)> query = [&](int l, int r, int pos) {
        int cnt = 0;
        for(auto [u, v] : G[pos]) cnt += uf.merge(u, v);
        if(l == r) {
            cout << uf.conn(Q[l].first, Q[l].second) << '\n';
            uf.revert(cnt);
            return;
        }
        int mid = (l + r) / 2;
        query(l, mid, pos << 1);
        query(mid + 1, r, pos << 1 | 1);
        uf.revert(cnt);
    };

    for(auto [u, v, a, b]: V) {
        update(1, C[M], a, b, 1, make_pair(u, v));
    }
    query(1, C[M], 1);

    return 0;
}