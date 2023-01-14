#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
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
const uint32_t N = 2e5 + OFFSET, M = 2e5 + OFFSET, K = 21;
template <size_t N,
          typename data_t,
          typename init_func = std::function<data_t(size_t)>,
          typename query_func =
            std::function<data_t(const data_t &, const data_t &)>>
class RMQ_ST {
protected:
  init_func ifunc;
  query_func qfunc;
  data_t f[(size_t)log2(N) + 1][N];
  size_t log_table[N];

public:
  RMQ_ST(init_func ifunc, query_func qfunc): ifunc(ifunc), qfunc(qfunc) {}
  void init(size_t n) {
    for (size_t i = 0; i <= n; ++i) f[0][i] = ifunc(i);
    for (size_t i = 1; i <= std::log2(n); ++i)
      for (size_t j = 0; j + (1 << i) - 1 <= n; ++j)
        f[i][j] = qfunc(f[i - 1][j], f[i - 1][j + (1 << (i - 1))]);
  }
  data_t query(size_t l, size_t r) const {
    size_t _ = std::log2(r - l + 1);
    return qfunc(f[_][l], f[_][r - (1 << _) + 1]);
  }
};
int a[N];
i64 sum[N];
RMQ_ST<N, int> max_a([](const size_t i) { return i; },
                     [](const int l, const int r) {
                       return a[l] < a[r] ? r : l;
                     });
RMQ_ST<N, i64> min_sum([](const size_t i) { return sum[i]; },
                       [](const i64 l, const i64 r) { return min(l, r); });
RMQ_ST<N, i64> max_sum([](const size_t i) { return sum[i]; },
                       [](const i64 l, const i64 r) { return max(l, r); });
bool dfs(int l, int r) {
  if (l >= r) return true;
  int now = max_a.query(l, r);
  i64 mins = min_sum.query(l - 1, now - 1), maxs = max_sum.query(now, r);
  if (a[now] < maxs - mins) return false;
  return dfs(l, now - 1) && dfs(now + 1, r);
}
auto solve() -> void {
  int n;
  cin >> n;
  _for(i, 1, n) cin >> a[i];
  _for(i, 1, n) sum[i] = sum[i - 1] + a[i];
  max_a.init(n);
  max_sum.init(n);
  min_sum.init(n);
  cout << (dfs(1, n) ? "YES\n" : "NO\n");
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
