#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
auto solve() -> void {
  i64 a, b, c;
  cin >> a >> b >> c;
  cout << a + b + c << " " << b + c << " " << c << '\n';
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
