// Tested
// Query O(logN) Update O(logN)
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