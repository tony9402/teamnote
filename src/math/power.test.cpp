// 1629
#include<bits/stdc++.h>

using namespace std;

template<typename T> T power(T a, T b, T mod) {
    T ret = 1;
    while(b) {
        if(b & 1) ret = ret * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    long long A, B, C; cin >> A >> B >> C;
    cout << power(A, B, C);

    return 0;
}