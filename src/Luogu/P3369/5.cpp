#include <bits/extc++.h>
using namespace std;
void solve1() {
  int n;
  cin >> n;
  __gnu_pbds::tree<pair<int, int>,
                   __gnu_pbds::null_type,
                   less<pair<int, int>>,
                   __gnu_pbds::rb_tree_tag,
                   __gnu_pbds::tree_order_statistics_node_update>
    tr;
  for (int i = 0, opt, x; i < n; ++i) {
    cin >> opt >> x;
    switch (opt) {
      case 1: tr.insert({x, i}); break;
      case 2: tr.erase(tr.lower_bound({x, 0})); break;
      case 3: cout << tr.order_of_key({x, 0}) + 1 << '\n'; break;
      case 4: cout << tr.find_by_order(x - 1)->first << '\n'; break;
      case 5: cout << (--tr.lower_bound({x, 0}))->first << '\n'; break;
      case 6: cout << tr.upper_bound({x, n})->first << '\n'; break;
    }
  }
}
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  solve1();
  return 0;
}
