#include <bits/stdc++.h>
using namespace std;
#define _run_continue(expressions) \
  {                                \
    expressions;                   \
    continue;                      \
  }
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int kase;
  cin >> kase;
  while (kase--) {
    i64 a, b, x, y;
    cin >> a >> b >> x >> y;
    i64 k = __gcd(a, b) * 2;
    if (x % k == 0 && y % k == 0) _run_continue(cout << "Y\n");
    if ((x + b) % k == 0 && (y + a) % k == 0) _run_continue(cout << "Y\n");
    if ((x + a) % k == 0 && (y + b) % k == 0) _run_continue(cout << "Y\n");
    if ((x + a + b) % k == 0 && (y + a + b) % k == 0)
      _run_continue(cout << "Y\n");
    cout << "N\n";
  __end_kase:;
  }
  return 0;
}
