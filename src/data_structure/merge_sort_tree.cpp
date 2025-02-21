template<typename T> struct MergesortTree {
    vector<vector<T>> tree;
    int siz;
    MergesortTree(int N) {
        for(siz = 1; siz < N; siz <<= 1);
        tree.resize(siz << 1);
    }
    void build(const vector<T> &V) {
        int N = (int)V.size();
        for(int i = 0; i < N; ++i) {
            tree[siz + i].push_back(V[i]);
        }
        for(int i = siz - 1; i; --i) {
            auto &L = tree[i << 1];
            auto &R = tree[i << 1 | 1];
            merge(L.begin(), L.end(), R.begin(), R.end(), back_inserter(tree[i]));
        }
    }
    int query(int l, int r, int s, int e, int pos, int k) {
        if(s <= l && r <= e) return tree[pos].end() - upper_bound(tree[pos].begin(), tree[pos].end(), k);
        if(e < l || r < s) return 0;
        int mid = (l + r) / 2;
        return query(l, mid, s, e, pos << 1, k) + query(mid + 1, r, s, e, pos << 1 | 1, k);
    }
    int query(int s, int e, int k) {
        return query(0, siz - 1, s, e, 1, k);
    }
};