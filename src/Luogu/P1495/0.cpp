#include <bits/stdc++.h>
using namespace std;
const int N = 15;
i64 a[N], b[N];
i64 exgcd(i64 a, i64 b, i64 &x, i64 &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  i64 d = exgcd(b, a % b, y, x);
  y -= a / b * x;
  return d;
}
int main() {
  int n;
  cin >> n;
  i64 mul = 1;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i] >> b[i];
    mul *= a[i];
  }
  i64 ans = 0;
  for (int i = 1; i <= n; ++i) {
    i64 _ = mul / a[i];
    i64 x, y;
    exgcd(_, a[i], x, y);
    ((x %= a[i]) += a[i]) %= a[i];
    (ans += b[i] * _ % mul * x % mul) %= mul;
  }
  cout << ans;
  return 0;
}
