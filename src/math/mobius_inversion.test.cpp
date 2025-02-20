// 1557
#include<bits/stdc++.h>

using namespace std;
using ll = long long;

vector<int> MobiusInversion(int N) {
    vector<int> mu(N + 1);
    mu[1] = 1;
    for(int i = 1; i <= N; ++i) {
        for(int j = i + i; j <= N; j += i) mu[j] -= mu[i];
    }
    return mu;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    const int mx = 1e6;
    vector<int> mu = MobiusInversion(mx);
    ll K; cin >> K;
    ll l = 0, r = 1e12;
    while(l <= r) {
        ll mid = (l + r) / 2;
        ll ret = 0;
        for(ll i = 1; i * i <= mid; ++i) {
            ll cnt = mid / i / i;
            ret += mu[i] * cnt;
        }
        if(ret < K) l = mid + 1;
        else r = mid - 1;
    }
    cout << l;

    return 0;
}