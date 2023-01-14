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
  int pre, cnt = 1;
  cin >> pre;
  bool f = 0;
  vector<int> ans;
  ans.reserve(n);
  _for(i, 2, n, x) {
    cin >> x;
    if (f) continue;
    if (x == pre) {
      ++cnt;
      continue;
    }
    if (f |= cnt < 2) continue;
    ans.push_back(i - 1);
    _for(j, i - cnt, i - 2) ans.push_back(j);
    pre = x;
    cnt = 1;
  }
  if (cnt < 2 || f) {
    cout << "-1\n";
    return;
  }
  ans.push_back(n);
  _for(j, n - cnt + 1, n - 1) ans.push_back(j);
  for (int i : ans) cout << i << ' ';
  cout << '\n';
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
