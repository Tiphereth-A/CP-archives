#include <bits/stdc++.h>
using namespace std;
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
auto solve() -> void {
  string s;
  cin >> s;
  if (s.size() == 2) {
    cout << s[1] << '\n';
    return;
  }
  char _ = 0x7f;
  int __ = 0;
  _for(i, 0, (int)s.size() - 1) {
    if (_ > s[i]) {
      __ = i;
      _ = s[i];
    }
  }
  cout << _ << '\n';
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
