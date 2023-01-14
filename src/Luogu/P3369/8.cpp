#include <bits/extc++.h>
std::vector<int> data;
auto solve1() {
  int idx = 0, n = data[idx++];
  __gnu_pbds::tree<std::pair<int, int>,
                   __gnu_pbds::null_type,
                   std::less<std::pair<int, int>>,
                   __gnu_pbds::rb_tree_tag,
                   __gnu_pbds::tree_order_statistics_node_update>
    rbtree;
  std::vector<int> result;
  result.reserve(n);
  for (int i = 0, opt, x; i < n; ++i) {
    opt = data[idx++];
    x = data[idx++];
    switch (opt) {
      case 1: rbtree.insert({x, i}); break;
      case 2: rbtree.erase(rbtree.lower_bound({x, 0})); break;
      case 3: result.push_back(rbtree.order_of_key({x, 0}) + 1); break;
      case 4: result.push_back(rbtree.find_by_order(x - 1)->first); break;
      case 5: result.push_back((--rbtree.lower_bound({x, 0}))->first); break;
      case 6: result.push_back(rbtree.upper_bound({x, n})->first); break;
    }
  }
  return result;
}
int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int n;
  std::cin >> n;
  data.resize(n * 2 + 1);
  data[0] = n;
  for (int i = 1; i < data.size(); i += 2) std::cin >> data[i] >> data[i + 1];
  auto result = solve1();
  for (auto &&i : result) std::cout << i << '\n';
  return 0;
}
