// 21162
#include<bits/stdc++.h>

using namespace std;

// 31, 998244353
template<long long C, long long HASH_MOD> struct Hashing {
    vector<long long> H, B;
    template<typename T> void build(const T& S) {
        H.resize(S.size() + 1);
        B.resize(S.size() + 1); B[0] = 1;
        for(int i = 1; i <= (int)S.size(); ++i) H[i] = (H[i - 1] * C + S[i - 1]) % HASH_MOD;
        for(int i = 1; i <= (int)S.size(); ++i) B[i] = B[i - 1] * C % HASH_MOD;
    }
    long long get(int s, int e) {
        long long ret = (H[e] - H[s - 1] * B[e - s + 1]) % HASH_MOD;
        if(ret < 0) ret += HASH_MOD;
        return ret;
    }
    void chk_setting() { assert(gcd(C, HASH_MOD) == 1); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, K; cin >> N >> K;
    vector<int> V(N);
    for(int i = 0; i < N; ++i) cin >> V[i];
    Hashing<31, 998244353> H;
    reverse(V.begin(), V.end());
    for(int i = 0; i < N - 1; ++i) V.emplace_back(V[i]);
    H.build(V);

    function<bool(int,int)> cmp = [&](int a, int b) -> bool {
        int l = 0, r = N - 1;
        while(l < r) {
            int mid = (l + r + 1) / 2;
            long long h1 = H.get(a + 1, a + mid), h2 = H.get(b + 1, b + mid);
            if(h1 == h2) l = mid;
            else r = mid - 1;
        }
        if(l == N - 1) return false;
        return V[a + l] < V[b + l];
    };
    vector<int> idx(N-1); iota(idx.begin(), idx.end(), 1);
    stable_sort(idx.begin(), idx.end(), cmp);
    for(int i = 0; i < N; ++i) cout << V[idx[K - 1] + i] << ' ';
    
    return 0;
}