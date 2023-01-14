#include <bits/stdc++.h>
using namespace std;
using i128 = __int128_t;
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
const int MOD = 1e9 + 7;
i128 exgcd(i128 a, i128 b, i128 &x, i128 &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  i128 res = exgcd(b, a % b, y, x);
  y -= a / b * x;
  return res;
}
i128 qpow(i128 a, i128 b, i128 mod = MOD) {
  i128 res = 1;
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
ostream &operator<<(ostream &os, i128 n) {
  if (n < 0) {
    os << '-';
    n = -n;
  }
  if (n > 9) os << (i128)(n / 10);
  os << (int)(n % 10);
  return os;
}
int main() {
  int kase;
  scanf("%d", &kase);
  while (kase--) {
    i128 c1, c2, e1, e2, n;
    i64 _c1, _c2, _e1, _e2, _n;
    scanf("%lld%lld%lld%lld%lld", &_c1, &_c2, &_e1, &_e2, &_n);
    if (_e1 > _e2) {
      swap(_e1, _e2);
      swap(_c1, _c2);
    }
    c1 = _c1;
    c2 = _c2;
    e1 = _e1;
    e2 = _e2;
    n = _n;
    while (e1) {
      i128 _ = e2 / e1, __ = qpow(c1, _, n);
      i128 x, y;
      exgcd(__, n, x, y);
      ((x %= n) += n) %= n;
      (c2 *= x) %= n;
      e2 %= e1;
      swap(e1, e2);
      swap(c1, c2);
    }
    printf("%lld\n", _c2 = c2);
  __end_kase:;
  }
FINISHED:
  return 0;
}
