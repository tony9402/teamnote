// 5615
#include<bits/stdc++.h>

using namespace std;
using ll = long long;

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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int tc; cin >> tc;
    int ans = 0;
    while(~--tc) {
        ll N; cin >> N;
        ans += isPrime(N * 2 + 1);
    }
    cout << ans;

    return 0;
}