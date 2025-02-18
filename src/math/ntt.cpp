// Tested
using ll = long long;
template<typename T> T power(T a, T b, T mod) {
    if(b == 0) return 1;
    if(~b & 1) return power(a * a % mod, b >> 1, mod);
    return a * power(a, b - 1, mod) % mod;
}
// (MOD) 104,857,601   =  25 * 2^22 + 1, w = 3
// (MOD) 998,244,353   = 119 * 2^23 + 1, w = 3
// (MOD) 2,281,701,377 =  17 * 2^27 + 1, w = 3
// (MOD) 2,483,027,969 =  37 * 2^26 + 1, w = 3
// (MOD) 2,113,929,217 =  63 * 2^25 + 1, w = 5
// (MOD) 1,092,616,193 = 521 * 2^21 + 1, w = 3
template<ll W, ll MOD> void NTT(vector<ll> &V, bool inv=false) {
    int N = (int)V.size();
    vector<ll> root(N >> 1);
    for(int i = 1, j = 0; i < N; ++i) {
        int bit = N >> 1;
        while(j >= bit) j -= bit, bit >>= 1;
        j += bit;
        if(i < j) swap(V[i], V[j]);
    }
    ll ang = power<ll>(W, (MOD - 1) / N, MOD);
    if(inv) ang = power<ll>(ang, MOD - 2, MOD);
    root[0] = 1;
    for(int i = 1; i * 2 < N; ++i) root[i] = root[i - 1] * ang % MOD;
    for(int i = 2; i <= N; i <<= 1) {
        int step = N / i;
        for(int j = 0; j < N; j += i) {
            for(int k = 0; k * 2 < i; ++k) {
                ll u = V[j | k], v = V[j | k | i >> 1] * root[step * k] % MOD;
                V[j | k] = (u + v) % MOD;
                V[j | k | i >> 1] = ((u - v) % MOD + MOD) % MOD;
            }
        }
    }
    if(inv) {
        ll t = power<ll>(N, MOD - 2, MOD);
        for(int i = 0; i < N; ++i) V[i] = V[i] * t % MOD;
    }
}
template<ll W, ll MOD> vector<ll> multiply(const vector<ll> &va, const vector<ll> &vb) {
    vector<ll> a(va.begin(), va.end()), b(vb.begin(), vb.end());
    int N = 2;
    while(N < a.size() + b.size()) N <<= 1;
    a.resize(N); b.resize(N);
    NTT<W, MOD>(a); NTT<W, MOD>(b);
    for(int i = 0; i < N; ++i) a[i] *= b[i];
    NTT<W, MOD>(a, true);
    return a;
}