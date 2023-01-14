#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
const uint32_t OFFSET = 5;
const uint32_t N = 1e5 + OFFSET, M = 2e5 + OFFSET, K = 21;
template <size_t N, typename Tp, bool _clear = false>
class BIT {
protected:
  Tp tree[N];
  constexpr size_t lowbit(ptrdiff_t x) const { return x & (-x); }

public:
  BIT() {}
  void clear() { memset(tree, 0, sizeof(tree)); }
  void modify(size_t pos, Tp val) {
    for (size_t i = pos; i < N; i += lowbit(i)) tree[i] = max(tree[i], val);
  }
  Tp query(size_t pos) const {
    Tp ret = 0;
    for (size_t i = pos; i; i = (ptrdiff_t)i - lowbit(i))
      ret = max(ret, tree[i]);
    return ret;
  }
};
BIT<N, int> tr;
int a[N];
int idx_b[N];
int f[N];
auto solve() -> void {
  int n;
  cin >> n;
  _for(i, 1, n) cin >> a[i];
  _for(i, 1, n, _) {
    cin >> _;
    idx_b[_] = i;
  }
  _for(i, 1, n) {
    _for(j, max(1, a[i] - 4), min(n, a[i] + 4)) f[j] = tr.query(idx_b[j] - 1);
    _for(j, max(1, a[i] - 4), min(n, a[i] + 4)) tr.modify(idx_b[j], f[j] + 1);
  }
  cout << tr.query(n);
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
