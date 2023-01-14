#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _all(a) (a).begin(), (a).end()
#define _run_return_void(expressions) \
  {                                   \
    expressions;                      \
    return;                           \
  }
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
bool _[26];
auto solve() -> void {
  i64 n, m;
  cin >> n >> m;
  vector<i64> v;
  v.reserve(n);
  _for(i, 1, n, x) {
    cin >> x;
    v.push_back(x);
  }
  if (m >= n)
    _run_return_void(cout << accumulate(_all(v), (i64)(0)) +
                               (n) * (m * 2 - n - 1) / 2
                          << '\n');
  i64 sum = 0, maxs = 0;
  _for(i, 0, n - 1) {
    sum += v[i];
    if (i >= m) sum -= v[i - m];
    chkmax(maxs, sum);
  }
  cout << maxs + m * (m - 1) / 2 << '\n';
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
