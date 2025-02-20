// 25563
#include<bits/stdc++.h>

using namespace std;

template<typename T> void SupersetZetaTransform(vector<T> &V) {
    int N = (int)V.size();
    assert((N & (N - 1)) == 0);
    for(int j = 1; j < N; j <<= 1) {
        for(int i = 0; i < N; ++i) {
            if(i & j) V[i ^ j] += V[i];
        }
    }
}

template<typename T> void SupersetMobiusTransform(vector<T> &V) {
    int N = (int)V.size();
    assert((N & (N - 1)) == 0);
    for(int j = 1; j < N; j <<= 1) {
        for(int i = 0; i < N; ++i) {
            if(i & j) V[i ^ j] -= V[i];
        }
    }
}

template<typename T> void SubsetZetaTransform(vector<T> &V) {
    int N = (int)V.size();
    assert((N & (N - 1)) == 0);
    for(int j = 1; j < N; j <<= 1) {
        for(int i = 0; i < N; ++i) {
            if(i & j) V[i] += V[i ^ j];
        }
    }
}

template<typename T> void SubsetMobiusTransform(vector<T> &V) {
    int N = (int)V.size();
    assert((N & (N - 1)) == 0);
    for(int j = 1; j < N; j <<= 1) {
        for(int i = 0; i < N; ++i) {
            if(i & j) V[i] -= V[i ^ j];
        }
    }
}

template<typename T> vector<T> AndConvolution(vector<T> A, vector<T> B) {
    SupersetZetaTransform(A);
    SupersetZetaTransform(B);
    for(int i = 0; i < A.size(); ++i) A[i] *= B[i];
    SupersetMobiusTransform(A);
    return A;
}

template<typename T> vector<T> OrConvolution(vector<T> A, vector<T> B) {
    SubsetZetaTransform(A);
    SubsetZetaTransform(B);
    for(int i = 0; i < A.size(); ++i) A[i] *= B[i];
    SubsetMobiusTransform(A);
    return A;
}

template<typename T> T AND(const vector<T> &A, const int K) {
    T ret = AndConvolution(A, A)[K];
    return ret - A[K] >> 1;
}

template<typename T> T OR(const vector<T> &A, const int K) {
    T ret = OrConvolution(A, A)[K];
    return ret - A[K] >> 1;
}

template<typename T> T XOR(const vector<T> &A, const int K) {
    T ret = 0;
    for(int i = 0; i < A.size(); ++i) ret += A[i] * A[i ^ K];
    if(K == 0) for(int x: A) ret -= x;
    return ret >> 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, K; cin >> N >> K;
    vector<long long> A(1 << 20);
    for(int i = 0; i < N; ++i) {
        int x; cin >> x;
        ++ A[x];
    }
    cout << AND(A, K) << " " << OR(A, K) << " " << XOR(A, K) << '\n';

    return 0;
}