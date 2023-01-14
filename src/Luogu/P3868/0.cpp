#include <bits/stdc++.h>
using namespace std;
typedef __int128_t i128;
const int N = 15;
i64 a[N], b[N];
i128 exgcd(i128 a, i128 b, i128 &x, i128 &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  i128 d = exgcd(b, a % b, y, x);
  y -= a / b * x;
  return d;
}
int main() {
  int n;
  cin >> n;
  i128 mul = 1;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  for (int i = 1; i <= n; ++i) cin >> b[i];
  for (int i = 1; i <= n; ++i) ((a[i] %= b[i]) += b[i]) %= b[i];
  for (int i = 1; i <= n; ++i) mul *= b[i];
  i128 ans = 0;
  for (int i = 1; i <= n; ++i) {
    i128 _ = mul / b[i];
    i128 x, y;
    exgcd(_, b[i], x, y);
    ((x %= b[i]) += b[i]) %= b[i];
    (ans += a[i] * _ % mul * x % mul) %= mul;
  }
  cout << (i64)ans;
  return 0;
}
