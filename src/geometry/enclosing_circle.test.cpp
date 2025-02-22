// 11930
#include<bits/stdc++.h>

using namespace std;

template<typename T> struct EnclosingCircle {
    int D;
    vector<T> P;
    EnclosingCircle(const vector<T> &_P, int _D):D(_D),P(_P) {}
    vector<T> train(T precision=-1, int epoch=100000, T learning_rate=0.1, T weight_decay=0.999) {
        vector<T> res(D);
        int N = (int)P.size() / D;
        for(int j = 0; j < D; ++j) {
            for(int i = 0; i < N; ++i) res[j] += P[i * D + j];
            res[j] /= N;
        }
        while(~--epoch) {
            T mx = 0; int mx_idx = 0;
            for(int i = 0; i < N; ++i) {
                T cur = cal(res, i);
                if(cur > mx) {
                    mx = cur;
                    mx_idx = i;
                }
            }
            T mx_dif = 0;
            for(int i = 0; i < D; ++i) {
                T dif = (P[mx_idx * D + i] - res[i]) * learning_rate;
                mx_dif = max(mx_dif, fabs(dif));
                res[i] += dif;
            }
            if(precision > 0 && mx_dif < precision) break;
            learning_rate *= weight_decay;
        }
        if(precision > 0) for(int i = 0; i < D; ++i) if(res[i] < 0 && res[i] > -precision) res[i] = -res[i];
        return res;
    }
    T cal(const vector<T> &x, int idx) {
        T ret = 0;
        for(int i = 0; i < D; ++i) {
            ret += (x[i] - P[idx * D + i]) * (x[i] - P[idx * D + i]);
        }
        return ret;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N; cin >> N;
    int D = 3;
    vector<long double> P(N * D);
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < D; ++j) cin >> P[i * D + j];
    }

    EnclosingCircle<long double> ec(P, D);
    auto it = ec.train(1e-3);
    long double r = 0.;
    for(int i = 0; i < N; ++i) r = max(r, sqrtl(ec.cal(it, i)));
    cout << setprecision(2) << fixed << r << '\n';

    return 0;
}