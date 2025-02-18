// 10531
#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using cpx = complex<double>;
void FFT(vector<cpx> &a, bool inv=false) {
    int N = (int)a.size();
    vector<cpx> root(N / 2);
    for(int i = 1, j = 0; i < N; ++i) {
        int bit = N >> 1;
        while(j >= bit) j -= bit, bit >>= 1;
        j += bit;
        if(i < j) swap(a[i], a[j]);
    }
    double ang = 2 * acos(-1) / N * (inv ? -1 : 1);
    for(int i = 0; i < N / 2; ++i) root[i] = cpx(cos(ang * i), sin(ang * i));
    /*
    XOR convolution: set roots[:] = 1.
    OR convolution: set roots[:] = 1 and do following
    if(!inv) a[j + k] = u + v, a[j + k + i / 2] = u;
    else a[j + k] = v, a[j + k + i / 2] = u - v;
    */
    for(int i = 2; i <= N; i <<= 1) {
        int step = N / i;
        for(int j = 0; j < N; j += i) {
            for(int k = 0; k < i / 2; ++k) {
                cpx u = a[j | k], v = a[j | k | i >> 1] * root[step * k];
                a[j | k] = u + v; a[j | k | i >> 1] = u - v;
            }
        }
    }
    if(inv) for(int i = 0; i < N; ++i) a[i] /= N;
}
vector<ll> multiply(const vector<ll> &va, const vector<ll> &vb) {
    vector<cpx> a(va.begin(), va.end()), b(vb.begin(), vb.end());
    int N = 2;
    while(N < a.size() + b.size()) N <<= 1;
    a.resize(N); b.resize(N);
    FFT(a); FFT(b);
    for(int i = 0; i < N; ++i) a[i] *= b[i];
    FFT(a, true);
    vector<ll> res(N);
    for(int i = 0; i < N; ++i) res[i] = llround(a[i].real());
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N; cin >> N;
    vector<ll> A(200001);
    A[0] = 1;
    for(int i = 0; i < N; ++i) {
        int x; cin >> x;
        A[x] = 1;
    }
    auto res = multiply(A, A);
    int M; cin >> M;
    int ans = 0;
    for(int i = 0; i < M; ++i) {
        int x; cin >> x;
        ans += !!res[x];
    }
    cout << ans;

    return 0;
}