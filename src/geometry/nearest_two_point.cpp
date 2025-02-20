// Tested
// Need Point(CCW) template
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