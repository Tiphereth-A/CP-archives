#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _run_return_void(expressions) \
  {                                   \
    expressions;                      \
    return;                           \
  }
#define _mid(l, r) ((l) + (((r) - (l)) >> 1))
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
const uint32_t OFFSET = 5;
const uint32_t N = 4e5 + OFFSET, M = 2e5 + OFFSET, K = 21;
template <size_t N, typename data_t, typename init_func, typename query_func>
class RMQ_ST {
protected:
  init_func ifunc;
  query_func qfunc;
  data_t f[(size_t)log2(N) + 1][N];
  size_t log_table[N];

public:
  RMQ_ST() {}
  void clear(size_t n) {
    for (size_t i = 0; i <= (size_t)(log2(n)); ++i)
      memset(f[i], 0, sizeof(f[i][0]) * (n + 1 - i));
  }
  void init(size_t n) {
    for (size_t i = 1; i <= n; ++i) f[0][i] = ifunc(i);
    for (size_t i = 1; i <= std::log2(n); ++i)
      for (size_t j = 1; j + (1 << i) - 1 <= n; ++j)
        f[i][j] = qfunc(f[i - 1][j], f[i - 1][j + (1 << (i - 1))]);
  }
  data_t query(size_t l, size_t r) const {
    size_t _ = std::log2(r - l + 1);
    return qfunc(f[_][l], f[_][r - (1 << _) + 1]);
  }
};
int a[N];
struct ifunc {
  int operator()(const size_t x) const { return a[x]; }
};
struct qfunc {
  int operator()(const int l, const int r) const { return gcd(l, r); }
};
RMQ_ST<N, int, ifunc, qfunc> tr;
bool judge(int n, int k) {
  int x = tr.query(1, k + 1);
  _for(l, 2, n)
    if (tr.query(l, l + k) != x) return false;
  return true;
}
auto solve() -> void {
  int n;
  cin >> n;
  _for(i, 1, n) cin >> a[i];
  bool f = 1;
  int x = a[1];
  _for(i, 2, n)
    if (a[i] != x) f = 0;
  if (f) _run_return_void(cout << "0\n");
  _for(i, 1, n) a[i + n] = a[i];
  tr.clear(n * 2);
  tr.init(n * 2);
  int l = 1, r = n, mid, ans = r;
  while (l <= r)
    if (judge(n, mid = _mid(l, r))) {
      ans = mid;
      r = mid - 1;
    } else l = mid + 1;
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
