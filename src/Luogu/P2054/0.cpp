#include <bits/stdc++.h>
using namespace std;
template <typename T = i64>
T qpow(__int128_t a, T b, T mod) {
  __int128_t res = 1;
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
template <typename T = i64>
T exgcd(T a, T b, T &x, T &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  T res = exgcd(b, a % b, y, x);
  y -= a / b * x;
  return res;
}
int main() {
  i64 n, m, l;
  cin >> n >> m >> l;
  i64 inv, k = qpow(2, m, n + 1);
  exgcd(k, n + 1, inv, k);
  ((inv %= n + 1) += n + 1) %= n + 1;
  cout << (i64)((__int128_t)inv * l % (n + 1));
  return 0;
}
