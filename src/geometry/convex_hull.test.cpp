#include<bits/stdc++.h>

using namespace std;
using ll = long long;

// Point Template
template<typename T> struct Point {
    T x, y;
    Point():Point(0, 0) { }
    Point(T _x, T _y):x(_x),y(_y) { }
    Point operator+(const Point &p) { return Point(x+p.x,y+p.y); }
    Point operator-(const Point &p) { return Point(x-p.x,y-p.y); }
    T operator*(Point p) { return x*p.y-y*p.x; }
    bool operator<(Point p) { return x == p.x ? y < p.y : x < p.x; }
    bool operator==(Point p) { return x == p.x && y == p.y; }
    template<typename OT> void operator=(Point<OT> p) { *this=Point(p.x,p.y); }
    void t() { swap(x, y); }
};
template<typename T> inline istream& operator>>(istream &in, Point<T> &o) { in >> o.x >> o.y; return in; }
template<typename T> inline ostream& operator<<(ostream &out, Point<T> &o) { out << o.x << ' ' << o.y; return out; }
// -1: 반시계, 0: 평행, 1: 시계
template<typename T> int ccw(Point<T> a, Point<T> b, Point<T> c) {
    T x = a * b + b * c + c * a;
    return (x > 0) - (x < 0);
}
template<typename T> T dist(Point<T> a, Point<T> b) {
    T x = (a.x - b.x), y = (a.y - b.y);
    return x * x + y * y;
}

template<typename T> vector<Point<T>> ConvexHull(vector<Point<T>> V) {
    swap(V[0], *min_element(V.begin(), V.end()));
    sort(V.begin() + 1, V.end(), [&](Point<T> a, Point<T> b) {
        int w = ccw(V[0], a, b);
        return w ? w > 0 : dist(V[0], a) < dist(V[0], b);
    });
    int idx = (int)V.size() - 1;
    while(idx > 1 && ccw(V[0], V[idx], V[idx - 1]) == 0) --idx;
    reverse(V.begin() + idx, V.end());
    vector<int> st;
    for(int i = 0; i < (int)V.size(); ++i) {
        // line ok < or <=
        while(st.size() > 1 && ccw(V[st[st.size() - 2]], V[st.back()], V[i]) < 0) st.pop_back();
        st.push_back(i);
    }
    vector<Point<T>> res;
    for(int x: st) res.push_back(V[x]);
    return res;
}
template<typename T> pair<Point<T>, Point<T>> get_far_two_point(vector<Point<T>> V) {
    int N = (int)V.size();
    T d = 0;
    pair<Point<T>, Point<T>> res;
    auto upd = [&](Point<T> a, Point<T> b) {
        T cur = dist(a, b);
        if(d < cur) d = cur, res = make_pair(a, b);
    };
    for(int i = 0, r = 0; i < N; ++i) {
        while(r + 1 < N && ccw(Point<T>(), V[(i + 1) % N] - V[i], V[(r + 1) % N] - V[r]) >= 0) upd(V[i], V[r++]);
        upd(V[i], V[r]);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int tc; cin >> tc;
    while(~--tc) {
        int N; cin >> N;
        vector<Point<ll>> V(N);
        for(int i = 0; i < N; ++i) cin >> V[i];
        auto [ans_a, ans_b] = get_far_two_point(ConvexHull(V));
        cout << ans_a << ' ' << ans_b << '\n';
    }

    return 0;
}