#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _foreach_cref(i, container) for (const auto &i : container)
#define _foreach_iter(it, container) \
  for (auto it = (container).begin(); it != (container).end(); ++it)
#define _all(a) (a).begin(), (a).end()
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
template <typename Tp>
class BIT {
protected:
  vector<Tp> tree;
  constexpr size_t lowbit(ptrdiff_t x) const { return x & (-x); }

public:
  explicit BIT(size_t n): tree(n) {}
  void modify(size_t pos, Tp val = 1) {
    for (size_t i = pos; i < tree.size(); i += lowbit(i)) tree[i] += val;
  }
  Tp query(size_t pos) const {
    Tp ret = 0;
    for (size_t i = pos; i; i = (ptrdiff_t)i - lowbit(i)) ret += tree[i];
    return ret;
  }
};
auto solve() -> void {
  int n;
  cin >> n;
  BIT<int> tr(n + 1);
  vector<int> a, idx;
  a.reserve(n);
  idx.reserve(n);
  _for(i, 1, n, x) {
    cin >> x;
    a.push_back(x);
    idx.push_back(x);
  }
  sort(_all(idx));
  idx.erase(unique(_all(idx)), idx.end());
  _foreach_iter(it, a) *it = lower_bound(_all(idx), *it) - idx.begin() + 1;
  i64 ans = 0;
  _foreach_cref(i, a) {
    ans += min(tr.query(i - 1), tr.query(n) - tr.query(i));
    tr.modify(i);
  }
  cout << ans << '\n';
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int _t;
  cin >> _t;
  while (_t--) solve();
  return 0;
}
