// 2042
#include<bits/stdc++.h>

using namespace std;

template<typename T>
struct Segment {
    vector<T> tree;
    int siz;

    Segment(int N = 1 << 17) {
        for(siz = 1; siz < N; siz <<= 1);
        tree = vector<T>(siz << 1);
    }
    void build() {
        for(int i = siz - 1; i > 0; --i) {
            tree[i] = tree[i << 1] + tree[i << 1 | 1];
        }
    }
    void update(int idx, T data) {
        tree[idx += siz] = data;
        while(idx >>= 1) tree[idx] = tree[idx << 1] + tree[idx << 1 | 1];
    }
    T query(int l, int r) {
        T ret_L = T(), ret_R = T();
        for(l += siz, r += siz; l <= r; l >>= 1, r >>= 1) {
            if(l & 1) ret_L = ret_L + tree[l ++];
            if(~r & 1) ret_R = tree[r --] + ret_R;
        }
        return ret_L + ret_R;
    }
    T& operator[](const int &idx) { return tree[idx + siz]; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M, K; cin >> N >> M >> K;
    Segment<long long> tree(N);
    for(int i = 0; i < N; ++i) cin >> tree[i];
    tree.build();
    for(int i = 0; i < M + K; ++i) {
        long long cmd, a, b; cin >> cmd >> a >> b;
        if(cmd == 1) tree.update(a - 1, b);
        else cout << tree.query(a - 1, b - 1) << '\n';
    }
    return 0;
}