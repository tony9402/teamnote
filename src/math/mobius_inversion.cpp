// Tested
vector<int> MobiusInversion(int N) {
    vector<int> mu(N + 1);
    mu[1] = 1;
    for(int i = 1; i <= N; ++i) {
        for(int j = i + i; j <= N; j += i) mu[j] -= mu[i];
    }
    return mu;
}