#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define foreach_ref_(i, container) for (auto &i : container)
#define foreach_binding_(container, vars...) for (auto &&[vars] : container)
auto solve([[maybe_unused]] int t_ = 0) -> void {
  int n;
  std::cin >> n;
  priority_queue<int, vector<int>, greater<int>> pq;
  vector<pair<int, int>> a(n);
  foreach_ref_(i, a) cin >> i.first >> i.second;
  sort(a.begin(), a.end(), [](auto const &lhs, auto const &rhs) {
    return lhs.first == rhs.first ? lhs.second > rhs.second :
                                    lhs.first < rhs.first;
  });
  foreach_binding_(a, t, val) {
    if (t > pq.size()) pq.push(val);
    else if (pq.top() < val) {
      pq.pop();
      pq.push(val);
    }
  }
  i64 ans = 0;
  while (!pq.empty()) {
    ans += pq.top();
    pq.pop();
  }
  cout << ans << '\n';
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
