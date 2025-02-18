// Tested
// 더 추가해야함.
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