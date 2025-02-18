// 23832
#include<bits/stdc++.h>

using namespace std;

template<typename T> struct EulerPhi {
    int N;
    bool isBig;
    vector<T> phi, primes;
    EulerPhi(int _N):N(_N) {
        if(N <= 5000000) {
            isBig = false;
            phi.resize(N + 1); iota(phi.begin(), phi.end(), 0);
            phi[0] = 0;
            for(int i = 2; i <= N; ++i) {
                if(phi[i] != i) continue;
                for(int j = i; j <= N; j += i) phi[j] = phi[j] / i * (i - 1);
            }
        }
        else {
            isBig = true;
            T sq = (T)sqrtl(N);
            vector<int> chk(sq + 1);
            for(T i = 2; i * i <= N; ++i) {
                if(chk[i]) continue;
                primes.push_back(i);
                for(T j = i + i; j * j <= N; j += i) chk[j] = 1;
            }
        }
    }
    T getPhi(T N) {
        if(N == 1) return 1;
        if(!isBig) return phi[N];
        T res = 1;
        for(T p: primes) {
            T x = 1;
            while(N % p == 0) x *= p, N /= p;
            res *= x - x / p;
        }
        if(N != 1) res *= N - 1;
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N; cin >> N;
    EulerPhi<int> ep(N);
    int ans = 0;
    for(int i = 2; i <= N; ++i) ans += ep.getPhi(i);
    cout << ans;
    return 0;
}