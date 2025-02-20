#include<bits/stdc++.h>

using namespace std;

template<typename T> struct Point {
    T x, y;
    Point():Point(0, 0) { }
    Point(T _x, T _y):x(_x),y(_y) { }
    Point operator+(Point p) { return Point(x+p.x,y+p.y); }
    Point operator-(Point p) { return Point(x-p.x,y-p.y); }
    T operator*(Point p) { return x*p.y-y*p.x; }
    bool operator==(Point p) const { return x == p.x && y == p.y; }
    bool operator<(Point p) const { return x == p.x ? y < p.y : x < p.x; }
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
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

template<typename T> T nearest_two_points(vector<Point<T>> P) {
    int N = (int)P.size();
    const T MIN = numeric_limits<T>::min();
    const T MAX = numeric_limits<T>::max();
    sort(P.begin(), P.end(), [&](Point<T> a, Point<T> b) {
        a.t(); b.t();
        return a < b;
    });
    set<Point<T>> st({P[0], P[1]});
    T ret = dist(P[0], P[1]);
    for(int i = 2, j = 0; i < N; ++i) {
        while(j < i && (P[i].y - P[j].y) * (P[i].y - P[j].y) >= ret) st.erase(P[j ++]);
        T d = sqrtl(ret) + 2;
        auto it1 = st.lower_bound(Point<T>(P[i].x - d, MIN));
        auto it2 = st.upper_bound(Point<T>(P[i].x + d, MAX));
        while(it1 != it2) ret = min(ret, dist(P[i], *it1 ++));
        st.insert(P[i]);
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N; cin >> N;
    vector<Point<long long>> P(N);
    for(int i = 0; i < N; ++i) cin >> P[i];
    cout << nearest_two_points(P);
}