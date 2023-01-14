#include <bits/stdc++.h>
using namespace std;
using i128 = __int128_t;
using i64 = int64_t;
const int N = 15;
i64 a[N], b[N];
ostream &operator<<(ostream &os, i128 n) {
  if (n < 0) {
    os << '-';
    n = -n;
  }
  if (n > 9) os << (i128)(n / 10);
  os << (uint_fast16_t)(n % 10);
  return os;
}
template <typename Tp = i64>
constexpr Tp mul_mod(Tp a, Tp b, const Tp &mod) {
  Tp d = floor(1.0l * a * b / mod + 0.5l), ret = a * b - d * mod;
  return ret < 0 ? ret + mod : ret;
}
void exgcd(i64 a, i64 b, i64 &x, i64 &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return;
  }
  exgcd(b, a % b, y, x);
  y -= a / b * x;
}
int main() {
  int n;
  cin >> n;
  i64 mul = 1;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i] >> b[i];
    mul *= a[i];
  }
  i128 ans = 0;
  for (int i = 1; i <= n; ++i) {
    i64 _ = mul / a[i];
    i64 x, y;
    exgcd(_, a[i], x, y);
    ((x %= a[i]) += a[i]) %= a[i];
    (ans += mul_mod(mul_mod(b[i], _, mul), x, mul)) %= mul;
  }
  cout << ans;
  return 0;
}
