#include <bits/stdc++.h>
using namespace std;
string str;
template <typename T = i64>
T qpow(T a, T b, T mod) {
  T res = 1;
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
int main() {
  i64 a, m;
  cin >> a >> m >> str;
  i64 mod = m, _ = m;
  for (i64 i = 2; i * i <= m; ++i)
    if (_ % i == 0) {
      mod -= mod / i;
      while (_ % i == 0) _ /= i;
    }
  if (_ > 1) mod -= mod / _;
  i64 b = 0;
  bool flag = 0;
  for (auto it = str.begin(); it != str.end(); ++it) {
    if (!isdigit(*it)) continue;
    (b *= 10) += *it - '0';
    if (b >= mod) {
      flag = 1;
      b %= mod;
    }
  }
  cout << qpow(a, b + flag * mod, m);
  return 0;
}
