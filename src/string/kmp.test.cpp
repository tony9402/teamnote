// 1786
#include<bits/stdc++.h>

using namespace std;

template<typename T> struct KMP {
    vector<int> fail;
    vector<int> failure(const T &Q) {
        fail.resize((int)Q.size() + 1);
        for(int i = 1, j = 0; i < (int)Q.size(); ++i) {
            while(j > 0 && Q[i] != Q[j]) j = fail[j - 1];
            if(Q[i] == Q[j]) fail[i] = ++j;
        }
        return fail;
    }
    vector<int> kmp(const T& P, const T& Q) {
        if(fail.size() == 0) failure(Q);
        vector<int> res;
        for(int i = 0, j = 0; i < (int)P.size(); ++i) {
            while(j > 0 && P[i] != Q[j]) j = fail[j - 1];
            if(P[i] == Q[j]) {
                if(j + 1 == (int)Q.size()) res.push_back(i - (int)Q.size() + 1), j = fail[j];
                else ++j;
            }
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string S; getline(cin, S);
    string T; getline(cin, T);
    if(S.size() == 0 && T.size() == 0) assert(false);
    KMP<string> kmp;
    auto it = kmp.kmp(S, T);
    cout << it.size() << '\n';
    for(auto x : it) cout << x + 1 << ' ';

    return 0;
}