#include <bits/stdc++.h>
using namespace std;
#define for_(i, l, r, vars...)                                            \
  for (std::make_signed_t<decltype(l + r)> i = (l), i##end = (r), ##vars; \
       i <= i##end;                                                       \
       ++i)
template <typename Tp>
class BIT {
protected:
  std::vector<Tp> tree;
  constexpr ptrdiff_t lowbit(ptrdiff_t x) const { return x & (-x); }

public:
  explicit BIT(size_t sz): tree(sz) {}
  void reset(size_t sz) { tree.resize(sz, 0); }
  void modify(ptrdiff_t pos, Tp val = 1) {
    for (ptrdiff_t i =
           std::clamp(pos, ptrdiff_t(0), ptrdiff_t(tree.size()) - 1);
         i < ptrdiff_t(tree.size());
         i += lowbit(i))
      tree[i] += val;
  }
  Tp query(ptrdiff_t pos) const {
    Tp ret = 0;
    for (ptrdiff_t i =
           std::clamp(pos, ptrdiff_t(0), ptrdiff_t(tree.size()) - 1);
         i;
         i = i - lowbit(i))
      ret += tree[i];
    return ret;
  }
};
auto solve([[maybe_unused]] int t_ = 0) -> void {
  string s;
  cin >> s;
  BIT<int> bt(s.size() * 2);
  int n = s.size();
  for_(i, 0, n - 1) bt.modify(i + 1, s[i] - '0');
  int w, m;
  cin >> w >> m;
  vector<vector<int>> vv(9);
  for_(i, 1, n - w + 1)
    vv[(bt.query(i + w - 1) % 9 + 9 - bt.query(i - 1) % 9) % 9].push_back(i);
  for_(i, 1, m, l, r, k) {
    cin >> l >> r >> k;
    int a = (bt.query(r) % 9 + 9 - bt.query(l - 1) % 9) % 9;
    pair<int, int> ans(INT_MAX, INT_MAX);
    for_(j_, 0, 8)
      for_(k_, 0, 8)
        if ((j_ * a + k_) % 9 == k) {
          if ((j_ == k_ && vv[j_].size() < 2) ||
              (j_ != k_ && (vv[j_].empty() || vv[k_].empty())))
            continue;
          if (j_ == k_) {
            ans = min(ans, make_pair(vv[j_][0], vv[j_][1]));
            continue;
          }
          ans = min(ans, make_pair(vv[j_][0], vv[k_][0]));
        }
    if (ans.first == INT_MAX) {
      cout << "-1 -1\n";
      continue;
    }
    cout << ans.first << ' ' << ans.second << '\n';
  }
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  int t_ = 0;
  std::cin >> t_;
  for (i_ = 0; i_ < t_; ++i_) solve(i_);
  return 0;
}
