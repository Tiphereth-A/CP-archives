#include <bits/stdc++.h>
using namespace std;
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
  cin >> s;
  int x = n / 2, y = x;
  while (y < n && s[y] == s[x]) ++y;
  cout << (y - x) * 2 - (n % 2) << '\n';
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
