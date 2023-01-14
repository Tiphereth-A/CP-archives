#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
int f(i64 x) {
  if (!x) return 1;
  int ans = 0;
  while (x) {
    i64 now = x % 10;
    if (now == 0 || now == 6 || now == 9) ++ans;
    else if (now == 8) ans += 2;
    x /= 10;
  }
  return ans;
}
auto solve() -> void {
  i64 n, k;
  cin >> n >> k;
  if (k == 0) {
    cout << n << '\n';
    return;
  }
  if (n < 0) n = -n;
  while (k && (n = f(n))) --k;
  if (k == 0) cout << n << '\n';
  else cout << ((k + 1) % 2) << '\n';
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
