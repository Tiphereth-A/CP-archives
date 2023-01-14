#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _run_break(expressions) \
  {                             \
    expressions;                \
    break;                      \
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
  int n, m;
  cin >> n;
  bitset<32> a;
  _for(i, 1, n, x) {
    cin >> x;
    _for(j, 0, 31)
      if (x & (1ll << j)) a.flip(j);
  }
  bool f = 1;
  _for(i, 1, 31)
    if (a[i] & n) _run_break(f = 0);
  cout << (f ? "YES\n" : "NO\n");
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
