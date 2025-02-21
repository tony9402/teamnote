// Tested
// (unsigned)chrono::steady_clock::now().time_since_epoch().count())
struct Random {
    mt19937 rd;
    Random() : rd(0x9402) {}
    Random(int seed) : rd(seed) {}
    template <typename T = int> T randint(T l = 0, T r = 32767) { return uniform_int_distribution<T>(l, r)(rd); }
    double randouble(double l = 0, double r = 1) { return uniform_real_distribution<double>(l, r)(rd); }
};