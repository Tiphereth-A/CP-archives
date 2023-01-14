#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _foreach_cref(i, container) for (const auto &i : container)
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
auto solve() -> void {
  int n;
  cin >> n;
  vector<int> v;
  v.reserve(n);
  _for(i, 1, n, x) {
    cin >> x;
    v.push_back(x);
  }
  int odds = count_if(_all(v), [](const int x) { return x & 1; });
  if (odds) _run_return_void(cout << n - odds << '\n');
  int _0 = 64;
  _foreach_cref(i, v) chkmin(_0, __builtin_ctz(i));
  cout << _0 + n - 1 << '\n';
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
