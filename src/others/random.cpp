// Tested
mt19937 rd = mt19937((unsigned)chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> ri(0, INT_MAX);
ri(rd)