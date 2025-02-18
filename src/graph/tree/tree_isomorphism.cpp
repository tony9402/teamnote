// Tested
// Need Graph Template
struct TreeIsomorphism {
    string tree_str;
    TreeIsomorphism(Graph<int> &G) {
        int N = G.size();
        function<vector<int>()> get_center = [&]() -> vector<int> {
            vector<int> ind(N), cand;
            for (int i = 0; i < N; ++i) {
                ind[i] = G[i].size();
                if (ind[i] < 2) cand.push_back(i);
            }
            int cnt = N;
            while (cnt > 2) {
                vector<int> tmp;
                for (int x : cand) {
                    --cnt;
                    for (int y : G[x]) if (--ind[y] == 1) tmp.push_back(y);
                }
                cand = tmp;
            }
            return cand;
        };

        function<string(int, int)> make_string = [&](int cur, int prev) -> string {
            vector<string> child;
            for (int nxt : G[cur]) {
                if (nxt == prev) continue;
                child.push_back(make_string(nxt, cur));
            }
            sort(child.begin(), child.end());
            string ret = "";
            for (const string &s : child) ret += s;
            return "(" + ret + ")";
        };

        if (N == 0) { }
        else {
            vector<int> center = get_center();
            if (center.size() == 1) tree_str = make_string(center[0], -1);
            else tree_str = min(make_string(center[0], -1), make_string(center[1], -1));
        }
    }
    string get() { return tree_str; }
};