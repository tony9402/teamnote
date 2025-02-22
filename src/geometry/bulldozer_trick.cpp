// Not Tested
// Not Tested, 9484 source code
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

struct Point {
    ll x, y;
    bool operator < (const Point &o) const { return tie(x, y) <  tie(o.x, o.y); }
    bool operator ==(const Point &o) const { return tie(x, y) == tie(o.x, o.y); }
};

struct Line {
    ll i, j, dx, dy;
    Line(int _i, int _j, const Point &pi, const Point &pj) {
        i = _i; j = _j;
        dx = pj.x - pi.x;
        dy = pj.y - pi.y;
    }
    bool operator< (const Line &l) const {
        ll left  = dy * l.dx;
        ll right = l.dy * dx;
        return tie(left, i, j) < tie(right, l.i, l.j);
    }
    bool operator==(const Line &l) const {
        return dy * l.dx == l.dy * dx;
    }
};

ll area(const Point &a, const Point &b, const Point &c) {
    return abs((b.x - a.x) * (c.y - b.y) - (c.x - b.x) * (b.y - a.y));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    while(true) {
        int N; cin >> N;
        if(N == 0) break;
        vector<Point> points(N + 1);
        for(int i = 1; i <= N; ++i) cin >> points[i].x >> points[i].y;
        sort(points.begin() + 1, points.end());
        vector<int> pos(N + 1);
        for(int i = 1; i <= N; ++i) pos[i] = i;

        vector<Line> V;
        for(int i = 1; i <= N; ++i) {
            for(int j = i + 1; j <= N; ++j) {
                V.emplace_back(i, j, points[i], points[j]);
            }
        }
        sort(V.begin(), V.end());

        ll mn = LLONG_MAX / 3, mx = LLONG_MIN / 3;
        for(int i = 0, j = 0; i < (int)V.size(); i = j) {
            while(j < (int)V.size() && V[i] == V[j]) ++j;
            for(int k = i; k < j; ++k) {
                int u = V[k].i, v = V[k].j;
                swap(pos[u], pos[v]); swap(points[pos[u]], points[pos[v]]);
                if(pos[u] > pos[v]) swap(u, v);
                if(pos[u] > 1) {
                    mn = min(mn, area(points[pos[u]], points[pos[v]], points[pos[u] - 1]));
                    mx = max(mx, area(points[pos[u]], points[pos[v]], points[1]));
                }
                if(pos[v] < N) {
                    mn = min(mn, area(points[pos[u]], points[pos[v]], points[pos[v] + 1]));
                    mx = max(mx, area(points[pos[u]], points[pos[v]], points[N]));
                }
            }
        }
        cout << mn / 2 << '.' << mn % 2 * 5 << ' ';
        cout << mx / 2 << '.' << mx % 2 * 5 << '\n';
    }

    return 0;
}