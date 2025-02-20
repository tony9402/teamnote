// Tested
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