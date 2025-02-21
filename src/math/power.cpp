// Tested
template<typename T> T power(T a, T b, T mod) {
    T ret = 1;
    while(b) {
        if(b & 1) ret = ret * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ret;
}