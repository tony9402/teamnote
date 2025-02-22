// Not Tested
// Not Tested, 17526 source code
#include<bits/stdc++.h>

#define p pair<ll, ll>
#define mp make_pair
using namespace std;
typedef long long ll;

ll arr[100005], l[100005], r[100005];
ll dp[100005];

struct CHT{
    p vc[100005];
    int siz=0;
    double cross(p x, p y){
        return 1.0 * (x.second - y.second) / (y.first - x.first);
    }

    void add(p x){
        while(siz >= 2 && cross(vc[siz-2], vc[siz-1]) >= cross(vc[siz-1],x))siz--;
        vc[siz++]=x;
    }

    ll query(int x){
        int s, e;
        s = 0, e = siz - 1;
        while(s != e){
            int m = (s + e) >> 1;
            if(vc[m].first * x + vc[m].second < vc[m+1].first * x + vc[m+1].second)e = m;
            else s = m + 1;
        }
        return vc[s].first * x + vc[s].second;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    CHT DCHT;
    int n;
    cin >> n;
    for(int i=n-1;i;i--)cin >> arr[i];
    for(int i=n-1;i;i--)cin >> l[i] >> r[i];
    for(int i=1;i<n;i++)arr[i] = arr[i] + arr[i-1];
    for(int i=1;i<n;i++){
        DCHT.add(mp(-arr[i-1], dp[i-1]));
        dp[i] = DCHT.query(r[i]) + arr[i] * r[i] + l[i];
    }
    cout << dp[n-1];
}
