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
  deque<int> v;
  _for(i, 1, n, x) {
    cin >> x;
    if (x < v.front()) v.push_front(x);
    else v.push_back(x);
  }
  _for(i, 0, n - 1) cout << v[i] << " \n"[i == n - 1];
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
