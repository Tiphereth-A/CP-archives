#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
const uint32_t OFFSET = 5;
const uint32_t N = 2e5 + OFFSET;
template <size_t N, typename Tp>
class BIT {
protected:
  Tp tree[N];
  constexpr size_t lowbit(ptrdiff_t x) const { return x & (-x); }

public:
  BIT() {}
  void clear(size_t n) { memset(tree, 0, sizeof(Tp) * (n + 1)); }
  void modify(size_t pos, size_t n, Tp val) {
    for (size_t i = pos; i <= n; i += lowbit(i)) tree[i] += val;
  }
  Tp query(size_t pos) const {
    Tp ret = 0;
    for (size_t i = pos; i; i = (ptrdiff_t)i - lowbit(i)) ret += tree[i];
    return ret;
  }
};
BIT<N, i64> tr;
auto solve() -> void {
  int n;
  cin >> n;
  tr.clear(n);
  i64 x, y, z;
  _for(i, 1, n) {
    cin >> x;
    tr.modify(i, n, x);
  }
  int q;
  cin >> q;
  _for(i, 1, q) {
    cin >> x >> y;
    if (x == 1) {
      cin >> z;
      tr.modify(y, n, z - (tr.query(y) - tr.query(y - 1)));
      continue;
    }
    int l = 0, r = n, mid;
    while (l < r)
      if (int mid = (l + r + 1) / 2; tr.query(mid) > y) r = mid - 1;
      else l = mid;
    cout << l << ' ' << (tr.query(n) + y - 1) / y << '\n';
  }
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
