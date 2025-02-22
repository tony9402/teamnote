// 6064
#include<bits/stdc++.h>

using namespace std;

template<typename T> pair<T, T> ext_gcd(T a, T b) {
    if(b == 0) return make_pair(1, 0);
    auto [u, v] = ext_gcd(b, a % b);
    return make_pair(v, u - a / b * v);
}

template<typename T> pair<T, T> crt(const vector<T> &A, const vector<T> &M) {
    int N = (int)A.size();
    T x = A[0], m = M[0];
    for(int i = 1; i < N; ++i) {
        T x2 = A[i], m2 = M[i];
        T g = gcd(m, m2);
        if(x % g != x2 % g) return make_pair(-1, -1);
        auto [p, q] = ext_gcd(m / g, m2 / g);
        T mod = m / g * m2;
        x = (x * (m2 / g) * q % mod + x2 * (m / g) * p % mod) % mod;
        if(x < 0) x += mod;
        m = mod;
    }
    return make_pair(x, m);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int tc; cin >> tc;
    while(~--tc) {
        vector<long long> A(2), M(2);
        for(int i = 0; i < 2; ++i) cin >> M[i];
        for(int i = 0; i < 2; ++i) cin >> A[i], --A[i];
        auto [a, b] = crt(A, M);
        if(a == -1) cout << -1 << '\n';
        else cout << a + 1 << '\n';
    }

    return 0;
}