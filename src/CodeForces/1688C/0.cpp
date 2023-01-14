#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _foreach_cref(i, container) for (const auto &i : container)
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
  string s;
  bitset<256> _;
  _for(i, 1, n * 2 + 1) {
    cin >> s;
    _foreach_cref(ch, s) _[ch].flip();
  }
  _for(i, 'a', 'z')
    if (_[i]) _run_return_void(cout << (char)i << '\n');
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
