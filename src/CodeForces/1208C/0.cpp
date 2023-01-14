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
  int n;
  cin >> n;
  _for(i, 0, n - 1)
    _for(j, 0, n - 1)
      cout << (((i >> 2) * (n >> 2) + (j >> 2)) << 4 | ((i & 3) << 2 | (j & 3)))
           << " \n"[j == n - 1];
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
