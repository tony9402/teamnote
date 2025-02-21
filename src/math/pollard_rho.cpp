
// 5615
// Need Random Template, Miller_rabin Template
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