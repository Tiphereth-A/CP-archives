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
  int x;
  cin >> x;
  int _1 = 0, _2 = 0, _3 = 0;
  _for(i, 0, 30)
    if (!(x & (1 << i))) _run_break(_1 = i);
  _for(i, 0, 30)
    if ((x & (1 << i))) _run_break(_2 = i);
  _for(i, 0, 30) _3 += !!(x & (1 << i));
  cout << (_3 > 1 ? (1 << _2) : ((1 << _1) | (1 << _2))) << '\n';
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
