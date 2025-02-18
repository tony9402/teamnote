// 1655
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type, less_equal<int>, rb_tree_tag,tree_order_statistics_node_update>
// multiset처럼 less<int> -> less_equal<int>

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    ordered_set pbds;
    int N; cin >> N;
    for(int i = 0; i < N; ++i) {
        int x; cin >> x;
        pbds.insert(x);
        cout << *pbds.find_by_order(i / 2) << '\n';
    }

    return 0;
}