// Not Tested, 12795 source code
// Not Tested, 12795 source code
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct Line {
    ll a, b;
    Line() : Line(0) { }
    Line(ll _a) : Line(_a, -1e18) { }
    Line(ll _a, ll _b) : a(_a), b(_b) { }
    ll operator[](const ll x) { return a * x + b; }
};

struct LiChao {
    struct Node {
        int l, r;
        ll xl, xr;
        Line line;
    };
    vector<Node> nodes;

    void init(ll xmn, ll xmx) {
        nodes.push_back({-1, -1, xmn, xmx, {0, static_cast<ll>(-1e18)}});
    }

    void insert(int pos, Line data) {
        ll xl = nodes[pos].xl, xr = nodes[pos].xr;
        ll xm = xl + xr >> 1;

        Line low = nodes[pos].line;
        Line high = data;
        if(low[xl] >= high[xl]) swap(low, high);
        if(low[xr] <= high[xr]) {
            nodes[pos].line = high;
            return;
        }
        else if(low[xm] <= high[xm]) {
            nodes[pos].line = high;
            if(!~nodes[pos].r) {
                nodes[pos].r = nodes.size();
                nodes.push_back({-1, -1, xm + 1, xr, {0, static_cast<ll>(-1e18)}});
            }
            insert(nodes[pos].r, low);
        }
        else {
            nodes[pos].line = low;
            if(!~nodes[pos].l) {
                nodes[pos].l = nodes.size();
                nodes.push_back({-1,-1,xl,xm,{0,static_cast<ll>(-1e18)}});
            }
            insert(nodes[pos].l, high);
        }
    }
    void insert(Line newLine) { insert(0, newLine); }

    ll get(int pos, ll x) {
        if(!~pos) return static_cast<ll>(-1e18);
        ll xl = nodes[pos].xl, xr = nodes[pos].xr;
        ll xm = xl + xr >> 1;
        if(x <= xm) return max(nodes[pos].line[x], get(nodes[pos].l, x));
        else return max(nodes[pos].line[x], get(nodes[pos].r, x));
    }
    ll get(ll x) { return get(0, x); }
};

LiChao tree;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int Q; cin >> Q;
    tree.init(-2e12, 2e12);
    while(Q --> 0) {
        int cmd; cin >> cmd;
        if(cmd == 1) {
            ll a, b; cin >> a >> b;
            tree.insert({a, b});
        }
        else {
            ll x; cin >> x;
            cout << tree.get(x) << '\n';
        }
    }

    return 0;
}