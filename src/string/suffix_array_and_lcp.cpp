// Tested
struct SuffixArray {
    vector<int> SA, LCP;
    int N;
    SuffixArray() { }
    SuffixArray(int N) {
        SA  = vector<int>(N);
        LCP = vector<int>(N);
    }
    SuffixArray(string S, int M = 26) {
        N   = S.size();
        S   = " " + S;
        SA  = vector<int>(N + 5);
        LCP = vector<int>(N + 5);

        // SuffixArray
        vector<int> cnt(max(M, N) + 1, 0), x(N + 1, 0), y(N + 1, 0);
        int i, j, k = 0;
        for (i = 1; i <= N; i++) cnt[x[i] = S[i] - 'a' + 1]++;
        for (i = 1; i <= M; i++) cnt[i] += cnt[i - 1];
        for (i = N; i > 0; i--) SA[cnt[x[i]]--] = i;
        for (int l = 1, p = 1; p < N; l <<= 1, M = p) {
            for (p = 0, i = N - l; ++i <= N;) y[++p] = i;
            for (i = 1; i <= N; i++) if (SA[i] > l) y[++p] = SA[i] - l;
            for (i = 0; i <= M; i++) cnt[i] = 0;
            for (i = 1; i <= N; i++) cnt[x[y[i]]]++;
            for (i = 1; i <= M; i++) cnt[i] += cnt[i - 1];
            for (i = N; i > 0; i--) SA[cnt[x[y[i]]]--] = y[i];
            swap(x, y); p = 1; x[SA[1]] = 1;
            for (i = 1; i < N; i++)
                x[SA[i + 1]] = SA[i] + l <= N && SA[i + 1] + l <= N && y[SA[i]] == y[SA[i + 1]] && y[SA[i] + l] == y[SA[i + 1] + l] ? p : ++p;
        }

        // LCP
        vector <int> rank(N + 1, 0);
        for (i = 1; i <= N; i++) rank[SA[i]] = i;
        for (i = 1; i <= N; LCP[rank[i++]] = k) for (k ? k-- : 0, j = SA[rank[i] - 1]; S[i + k] == S[j + k]; k++);
    }
};