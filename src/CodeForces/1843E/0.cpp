#include <bits/stdc++.h>
using ll = long long;
using i64 = ll;
#define for_(i, l, r, v...) for (ll i = (l), i##e = (r), ##v; i <= i##e; ++i)
template <typename... Ts>
void dec(Ts &...x) {
  ((--x), ...);
}
template <typename... Ts>
void inc(Ts &...x) {
  ((++x), ...);
}
using namespace std;
template <typename Tp>
class BIT {
protected:
  std::vector<Tp> tree;
  constexpr ptrdiff_t lowbit(ptrdiff_t x) const { return x & (-x); }

public:
  explicit BIT(size_t sz): tree(sz) {}
  void reset(size_t sz) { tree.resize(sz, 0); }
  void modify(ptrdiff_t pos, Tp val = 1) {
    if (pos < 1) return;
    pos = std::clamp(pos, ptrdiff_t(1), ptrdiff_t(tree.size()) - 1);
    for (ptrdiff_t i = pos; i < ptrdiff_t(tree.size()); i += lowbit(i))
      tree[i] += val;
  }
  Tp query(ptrdiff_t pos) const {
    Tp ret = 0;
    if (pos < 1) return 0;
    pos = std::clamp(pos, ptrdiff_t(1), ptrdiff_t(tree.size()) - 1);
    for (ptrdiff_t i = pos; i; i = i - lowbit(i)) ret += tree[i];
    return ret;
  }
};
void solve(int t_ = 0) {
  int n, m;
  cin >> n >> m;
  vector<pair<int, int>> v(m);
  for (auto &[l, r] : v) cin >> l >> r;
  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());
  int q;
  cin >> q;
  vector<i64> x(q + 1);
  for_(i, 1, q) cin >> x[i];
  BIT<i64> tr(n + 1);
  auto upd = [&](int from, int to) -> void {
    i64 diff = from > to ? -1 : 1;
    for_(i, min(from, to) + 1, max(from, to)) tr.modify(x[i], diff);
  };
  auto chk = [&]() -> bool {
    for (auto [l, r] : v) {
      if ((tr.query(r) - tr.query(l - 1)) * 2 > r - l + 1) { return true; }
    }
    return false;
  };
  upd(0, q);
  if (!chk()) {
    cout << "-1\n";
    return;
  }
  int l = 1, r = q;
  int pre = q, ans = q;
  while (r >= l) {
    int mid = l + (r - l) / 2;
    upd(pre, mid);
    pre = mid;
    if (chk()) {
      ans = mid;
      r = mid - 1;
    } else l = mid + 1;
  }
  cout << ans << '\n';
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  int t_ = 0;
  std::cin >> t_;
  for (i_ = 0; i_ < t_; ++i_) solve(i_);
  return 0;
}
