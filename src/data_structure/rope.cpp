// Tested
#include<ext/rope>
using namespace __gnu_cxx;
string S; crope rp = S.c_str();
rp.push_back('a');
rp.insert(0, "asdf");
rp.erase(0, 1);
rp.replace(0, 1, "asdf");
rp.substr(0, 2); // idx, cnt
rp.pop_back();
rp += rp2;