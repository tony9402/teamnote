// 16994
#include<bits/stdc++.h>
#include<ext/rope>

using namespace std;
using namespace __gnu_cxx;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string S; cin >> S;
    rope<char> rp = S.data();
    int N = (int)S.size();
    int Q; cin >> Q;
    while(~--Q) {
        int cmd, x, y; cin >> cmd;
        if(cmd == 1) {
            cin >> x >> y;
            rp = rp.substr(x, y - x + 1) + rp.substr(0, x) + rp.substr(y + 1, N);
        }
        else if(cmd == 2) {
            cin >> x >> y;
            rp = rp.substr(0, x) + rp.substr(y + 1, N) + rp.substr(x, y - x + 1);
        }
        else if(cmd == 3) {
            cin >> x;
            cout << rp.at(x) << '\n';
        }
    }

    return 0;
}