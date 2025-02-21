
// 5615
#include<bits/stdc++.h>

using namespace std;
using ll = long long;

struct Random {
    mt19937 rd;
    Random() : rd(0x9402) {}
    Random(int seed) : rd(seed) {}
    template <typename T = int> T randint(T l = 0, T r = 32767) { return uniform_int_distribution<T>(l, r)(rd); }
    double randouble(double l = 0, double r = 1) { return uniform_real_distribution<double>(l, r)(rd); }
};

ll Mul(ll x, ll y, ll MOD) {
    ll ret = x * y - MOD * (unsigned long long)(1.L / MOD * x * y);
    return ret + MOD * (ret < 0) - MOD * (ret >= (ll)MOD);
}
template<typename T> T power(T a, T b, T mod) {
    T ret = 1;
    while(b) {
        if(b & 1) ret = Mul(ret, a, mod);
        a = Mul(a, a, mod);
        b >>= 1;
    }
    return ret;
}
bool MillerRabin(ll a, ll b) {
    if(a % b == 0) return false;
    for(ll d = a - 1; ; d >>= 1) {
        ll cur = power<ll>(b, d, a);
        if(d & 1) return cur != 1 && cur != a - 1;
        if(cur == a - 1) return false;
    }
    return true;
}
bool isPrime(ll x) {
    if(x == 2 || x == 3 || x == 5 || x == 7) return true;
    if(x % 2 == 0 || x % 3 == 0 || x % 5 == 0 || x % 7 == 0) return false;
    if(x < 121) return x > 1;
    if(x < (1ULL << 32)) {
        for(const ll &y: {2, 7, 61}) {
            if(x == y) return true;
            if(x > y && MillerRabin(x, y)) return false;
        }
    }
    else {
        for (const ll &y : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
            if(x == y) return true;
            if(x > y && MillerRabin(x, y)) return false;
        }
    }
    return true;
}
Random Rand;
void _factorize(ll N, vector<ll> &V) {
    if(N == 1) return;
    if(~N & 1) {
        V.push_back(2);
        _factorize(N >> 1, V);
        return;
    }
    if(isPrime(N)) {
        V.push_back(N);
        return;
    }
    ll a, b, c, g = N;
    auto F = [&](ll x) -> ll { return (c + Mul(x, x, N)) % N; };
    do {
        if(g == N) {
            a = b = Rand.randint(0LL, N - 3) + 2;
            c = Rand.randint(0LL, 19LL) + 1;
        }
        a = F(a);
        b = F(F(b));
        g = gcd(abs(a - b), N);
    } while(g == 1);
    _factorize(g, V); _factorize(N / g, V);
}
vector<ll> factorize(ll N) {
    vector<ll> res;
    _factorize(N, res);
    sort(res.begin(), res.end());
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll N; cin >> N;
    for(const ll &x: factorize(N)) cout << x << '\n';

    return 0;
}