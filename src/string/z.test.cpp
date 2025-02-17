// 13576
#include<bits/stdc++.h>

using namespace std;

template<typename T>vector<int> Z(const T &V) {
    int N = (int)V.size();
    vector<int> ret(N); ret[0] = N;
    for(int i = 1, l = 0, r = 0; i < N; ++i) {
        if(i < r) ret[i] = min(r - i - 1, ret[i - l]);
        while(i + ret[i] < N && V[i + ret[i]] == V[ret[i]]) ++ ret[i];
        if(i + ret[i] > r) r = i + ret[i], l = i;
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string S; cin >> S;
    int N = (int)S.size();
    vector<int> z = Z(S);
    vector<int> res = z; 
    sort(res.begin(), res.end());
    vector<pair<int, int>> ans;
    for(int i = N - 1, j = N - 1; i >= 0; --i) {
        if(i + z[i] == N) {
            ans.emplace_back(z[i], res.end() - lower_bound(res.begin(), res.end(), z[i]));
        }
    }
    cout << (int)ans.size() << '\n';
    for(const auto &[x, y]: ans) cout << x << ' ' << y << '\n';

    return 0;
}