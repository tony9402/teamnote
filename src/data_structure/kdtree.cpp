// Tested
// Time Complexity: Build O(Nlog^2N) Query O(logN)
template<typename T> inline T INF() { return numeric_limits<T>::max() / 2; }
template<typename T> inline T square(T x) { return x * x; }
template<typename T> struct KDTree {
    // axis == 1 ? y : x
    struct Node {
        T x, y;
        int axis;
        T mnx, mxx, mny, mxy;

        Node() {
            mnx = mny = INF<T>();
            mxx = mxy = -INF<T>();
            axis = 0;
        }
        void update(T y, T x) {
            mnx = min(mnx, x); mny = min(mny, y);
            mxx = max(mxx, x); mxy = max(mxy, y);
        }
        T dis(pair<T, T> point) {
            T a = point.first - y, b = point.second - x;
            return square(a) + square(b);
        }
        bool operator==(pair<T, T> point) { return make_pair(y, x) == point; }
        bool operator!=(pair<T, T> point) { return make_pair(y, x) != point; }
        bool operator<(pair<T, T> point) { return make_pair(y, x) < point; }
        bool operator>(pair<T, T> point) { return make_pair(y, x) > point; }
    };

    vector<pair<T, T>> points;
    vector<Node> tree;
    vector<bool> exist;
    T query_answer;
    int siz;
    KDTree(int N = 1 << 17) {
        for(siz = 1; siz < N; siz <<= 1);
        tree.resize(siz << 1);
        exist.resize(siz << 1);
    }
    KDTree(const vector<pair<T, T>> &V) : KDTree(V.size()) { points = V; }
    void build(int l, int r, int pos) {
        Node cur;
        for(int i = l; i <= r; ++i) {
            auto [y, x] = points[i];
            cur.update(y, x);
        }
        tree[pos] = cur;
        exist[pos] = true;
        if(pos == 1) tree[pos].axis = 0;
        else tree[pos].axis = 1 - tree[pos >> 1].axis;
        if(tree[pos].axis) sort(points.begin() + l, points.begin() + r + 1);
        else sort(points.begin() + l, points.begin() + r + 1, [&](const pair<T, T> &a, const pair<T, T> &b) { return a.second != b.second ? a.second < b.second : a.first < b.first; });
        int mid = (l + r) / 2;
        tree[pos].y = points[mid].first;
        tree[pos].x = points[mid].second;
        if(l <= mid - 1) build(l, mid - 1, pos << 1);
        if(mid + 1 <= r) build(mid + 1, r, pos << 1 | 1);
    }
    void build() { build(0, (int)points.size() - 1, 1); }
    void query(int pos, pair<T, T> point) {
        if(tree[pos] != point) query_answer = min(query_answer, tree[pos].dis(point));
        if(tree[pos].axis) { // y
            if(point.first < tree[pos].y) {
                if(exist[pos << 1]) query(pos << 1, point);
                if(exist[pos << 1 | 1] && square(tree[pos << 1 | 1].mny - point.first) < query_answer) query(pos << 1 | 1, point);
            }
            else {
                if(exist[pos << 1 | 1]) query(pos << 1 | 1, point);
                if(exist[pos << 1] && square(tree[pos << 1].mxy - point.first) < query_answer) query(pos << 1, point);
            }
        }
        else {
            if(point.second < tree[pos].x) {
                if(exist[pos << 1]) query(pos << 1, point);
                if(exist[pos << 1 | 1] && square(tree[pos << 1 | 1].mnx - point.second) < query_answer) query(pos << 1 | 1, point);
            }
            else {
                if(exist[pos << 1 | 1]) query(pos << 1 | 1, point);
                if(exist[pos << 1] && square(tree[pos << 1].mxx - point.second) < query_answer) query(pos << 1, point);
            }
        }
    }
    T query(pair<T, T> point) {
        query_answer = INF<T>();
        query(1, point);
        return query_answer;
    }
};