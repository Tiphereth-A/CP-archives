#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
#define _foreach_ref(i, container) for (auto &i : container)
#define _foreach_cref(i, container) for (const auto &i : container)
using data_t = uint32_t;
using query_type = tuple<data_t, data_t, data_t>;
template <typename _T, const std::size_t _N>
class BIT {
private:
  _T tree[_N];
  constexpr std::size_t lowbit(std::ptrdiff_t x) { return x & (-x); }

public:
  BIT() {}
  void add(std::size_t pos, _T val = 1) {
    for (std::size_t i = pos; i < _N; i += lowbit(i)) tree[i] ^= val;
  }
  _T query(std::size_t pos) {
    _T ret = 0;
    for (std::size_t i = pos; i; i = (std::ptrdiff_t)i - lowbit(i))
      ret ^= tree[i];
    return ret;
  }
};
const int N = 1e6 + 5;
BIT<data_t, N> tr;
vector<data_t> a, b;
vector<query_type> q;
data_t sum[N], ans[N];
data_t pre[N], now[N];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n;
  cin >> n;
  a.reserve(n + 1);
  a.push_back(0);
  b.reserve(n + 1);
  b.push_back(0);
  _for(i, 1, n, x) {
    cin >> x;
    a.push_back(x);
    b.push_back(x);
  }
  _for(i, 1, n) sum[i] = sum[i - 1] ^ a[i];
  sort(b.begin(), b.end());
  b.erase(unique(b.begin(), b.end()), b.end());
  _foreach_ref(i, a) i = lower_bound(b.begin(), b.end(), i) - b.begin();
  _for(i, 1, n) {
    pre[i] = now[a[i]];
    now[a[i]] = i;
  }
  int m;
  cin >> m;
  q.reserve(m);
  _for(i, 1, m, l, r) {
    cin >> l >> r;
    q.emplace_back(l, r, i);
  }
  sort(q.begin(), q.end(), [](const query_type &lhs, const query_type &rhs) {
    return get<1>(lhs) < get<1>(rhs);
  });
  data_t now_idx = 1;
  _foreach_cref(i, q) {
    while (now_idx <= get<1>(i)) {
      if (pre[now_idx]) tr.add(pre[now_idx], b[a[now_idx]]);
      tr.add(now_idx, b[a[now_idx]]);
      ++now_idx;
    }
    ans[get<2>(i)] = tr.query(get<1>(i)) ^ tr.query(get<0>(i) - 1) ^
                     sum[get<1>(i)] ^ sum[get<0>(i) - 1];
  }
  _for(i, 1, m) cout << ans[i] << '\n';
  return 0;
}
