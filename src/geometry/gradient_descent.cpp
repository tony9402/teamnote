// Tested
template<typename T> struct GradientDescent {
    const long double eps = 0.0000001;
    int D;
    vector<T> P;
    GradientDescent(const vector<T> &_P, int _D):D(_D),P(_P) {}
    vector<T> train(T precision=-1, int epoch=100000, T learning_rate=1000000, T weight_decay=0.999) {
        vector<T> res(D);
        int N = (int)P.size() / D;
        for(int j = 0; j < D; ++j) {
            for(int i = 0; i < N; ++i) res[j] += P[i * D + j];
            res[j] /= N;
        }
        while(~--epoch) {
            vector<T> g = gradient(res);
            if(g.empty()) break;
            T mx_dif = 0;
            for(int i = 0; i < D; ++i) {
                res[i] -= learning_rate * g[i];
                mx_dif = max(mx_dif, fabs(g[i]));
            }
            if(precision > 0 && mx_dif < precision) break;
            learning_rate *= weight_decay;
        }
        if(precision > 0) for(int i = 0; i < D; ++i) if(res[i] < 0 && res[i] > -precision) res[i] = -res[i];
        return res;
    }
    // Customizing
    vector<T> f(const vector<T> &V) {
        int N = (int)P.size() / D;
        vector<T> ret(N);
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < D; ++j) {
                ret[i] += (P[i * D + j] - V[j] + eps) * (P[i * D + j] - V[j] + eps);
            }
            ret[i] = sqrtl(ret[i]);
        }
        return ret;
    }
    vector<T> gradient(const vector<T> &V) {
        vector<T> W = f(V);
        for(int i = 0; i < D; ++i) if(W[i] < 0.0000001) return {};
        int N = (int)P.size() / D;
        vector<T> res(D);
        for(int j = 0; j < D; ++j) {
            for(int i = 0; i < N; ++i) {
                res[j] += (V[j] - P[i * D + j]) / W[i];
            }
        }
        return res;
    }
};