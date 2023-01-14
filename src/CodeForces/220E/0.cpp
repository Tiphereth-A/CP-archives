#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _all(a) (a).begin(), (a).end()
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
template <size_t N, typename Tp>
class BIT {
protected:
  Tp tree[N];
  constexpr size_t lowbit(ptrdiff_t x) const { return x & (-x); }

public:
  BIT() {}
  Tp cnt;
  void modify(size_t pos, Tp val = 1) {
    ++cnt;
    for (size_t i = pos; i < N; i += lowbit(i)) tree[i] += val;
  }
  Tp query(size_t pos) const {
    Tp ret = 0;
    for (size_t i = pos; i; i = (ptrdiff_t)i - lowbit(i)) ret += tree[i];
    return ret;
  }
};
BIT<N, int> trl, trr;
int a[N];
auto solve() -> void {
  int n;
  i64 k;
  cin >> n >> k;
  vector<int> b;
  b.reserve(n);
  _for(i, 1, n) cin >> a[i];
  _for(i, 1, n) b.push_back(a[i]);
  sort(_all(b));
  b.erase(unique(_all(b)), b.end());
  _for(i, 1, n) a[i] = lower_bound(_all(b), a[i]) - b.begin() + 1;
  i64 inv_cnt = 0;
  _for(i, 1, n) {
    inv_cnt += trr.cnt - trr.query(a[i]);
    trr.modify(a[i]);
  }
  if (inv_cnt <= k) {
    cout << (i64)n * (n - 1) / 2;
    return;
  }
  int l = 1, r = 1;
  i64 ans = 0;
  for (; l < n && r <= n; ++l) {
    if (l == r) {
      inv_cnt -= trl.cnt - trl.query(a[r]) + trr.query(a[r] - 1);
      trr.modify(a[r++], -1);
    }
    inv_cnt += trl.cnt - trl.query(a[l]) + trr.query(a[l] - 1);
    trl.modify(a[l]);
    while (inv_cnt > k && r <= n) {
      inv_cnt -= trl.cnt - trl.query(a[r]) + trr.query(a[r] - 1);
      trr.modify(a[r++], -1);
    }
    ans += n - r + 1;
  }
  cout << ans;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
