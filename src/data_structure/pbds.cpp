// Tested
// 시간복잡도 set이랑 동일하다고 보면 됨.
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type, less_equal<int>, rb_tree_tag,tree_order_statistics_node_update>
// multiset처럼 less_equal<int>
// set처럼 less<int>
ordered_set pbds;
pbds.insert(x);
pbds.erase(x); // multiset처럼 쓸 때 주의
*pbds.find_by_order(x);
*pbds.find_by_key(x);