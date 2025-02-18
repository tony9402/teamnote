// Tested
mt19937 rd = mt19937(0x9402);
uniform_int_distribution<int> ri(0, INT_MAX);
ri(rd);