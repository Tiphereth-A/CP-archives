#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
const uint32_t OFFSET = 5;
const uint32_t N = 5e5 + OFFSET, M = 5e5 + OFFSET, K = 21;
map<int, int> idx;
int pos[N];
struct Seq {
  int l, r;
} s[N];
int cnt_s;
template <size_t N, typename data_t, typename init_func, typename query_func>
class RMQ_ST {
protected:
  init_func ifunc;
  query_func qfunc;
  data_t f[(size_t)log2(N) + 1][N];
  size_t log_table[N];

public:
  RMQ_ST() {}
  void clear() { memset(f, 0, sizeof(f)); }
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
struct ifunc {
  int operator()(const size_t n) const { return s[n].r - s[n].l; }
};
struct qfunc {
  int operator()(const int l, const int r) const { return std::min(l, r); }
};
RMQ_ST<N, int, ifunc, qfunc> st;
auto solve() -> void {
  int n, m;
  cin >> n >> m;
  _for(i, 1, n, x, pre) {
    cin >> x;
    if ((pre = idx[x]) && (pre > s[cnt_s].l)) s[++cnt_s] = {pre, i};
    idx[x] = i;
  }
  st.init(cnt_s);
  _for(i, 1, m, x, y, l, r) {
    cin >> x >> y;
    l = lower_bound(s + 1,
                    s + cnt_s + 1,
                    x,
                    [](const Seq &it, int v) -> bool { return it.l < v; }) -
        s;
    r = upper_bound(s + 1,
                    s + cnt_s + 1,
                    y,
                    [](int v, const Seq &it) -> bool { return it.r > v; }) -
        s - 1;
    cout << (l <= r ? st.query(l, r) : -1) << '\n';
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
