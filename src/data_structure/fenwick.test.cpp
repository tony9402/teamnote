// 2042
#include<bits/stdc++.h>

using namespace std;

template<typename T> struct Fenwick {
    int N;
    vector<T> tree;
    Fenwick(int _N):N(_N) { tree.resize(N + 1); }
    void update(int idx, T data) {
        for( ; idx <= N; idx += idx & -idx) tree[idx] += data;
    }
    T query(int idx) {
        T ret = 0;
        for( ; idx; idx -= idx & -idx) ret += tree[idx];
        return ret;
    }
    T query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M, K; cin >> N >> M >> K;
    Fenwick<long long> tree(N + 1);
    vector<long long> V(N + 1);
    for(int i = 1; i <= N; ++i) {
        cin >> V[i];
        tree.update(i, V[i]);
    }
    for(int i = 0; i < M + K; ++i) {
        int cmd; cin >> cmd;
        long long a, b; cin >> a >> b;
        if(cmd == 1) {
            tree.update(a, b - V[a]);
            V[a] = b;
        }
        else {
            cout << tree.query(a, b) << '\n';
        }
    }

    return 0;
}