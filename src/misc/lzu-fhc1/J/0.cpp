#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ldb = long double;
const ldb PI = acos(-1.0l);
ldb __(i64 a, i64 b, i64 c) {
  ldb _a = a + b, _b = a + c, _c = c + b;
  return ((PI - acos((_a * _a + _b * _b - _c * _c) / (2 * _a * _b))) * _b +
          (PI - acos((_a * _a + _c * _c - _b * _b) / (2 * _a * _c))) * _c) /
         (PI * c);
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int _t;
  cin >> _t;
  while (_t--) {
    i64 a, b, c;
    cin >> a >> b >> c;
    cout << fixed << setprecision(12)
         << min(
              min(__(a, b, c), __(a, c, b)),
              min(min(__(b, a, c), __(b, c, a)), min(__(c, a, b), __(c, b, a))))
         << '\n';
  }
  return 0;
}
