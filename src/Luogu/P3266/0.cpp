#include <bits/stdc++.h>
using i64 = int64_t;
using namespace std;
const i64 MOD = 1e9 + 7;
const int N = 2e7 + 5;
int fact[N];
constexpr i64 qpow(i64 a, i64 b) {
  i64 res = 1;
  for (; b; b >>= 1, a = a * a % MOD)
    if (b & 1) res = res * a % MOD;
  return res;
}
i64 c(i64 n, i64 m) {
  if (n < 0 || m < 0 || n < m) return 0;
  return fact[n] * qpow(fact[m], MOD - 2) % MOD * qpow(fact[n - m], MOD - 2) %
         MOD;
}
i64 n, m;
i64 g(i64 x, i64 y);
i64 f(i64 x, i64 y) {
  if (x < 0 || y < 0) return 0;
  return (c(x + y, y) + MOD - g(y + m + 2, x - m - 2)) % MOD;
}
i64 g(i64 x, i64 y) {
  if (x < 0 || y < 0) return 0;
  return (c(x + y, y) + MOD - f(y - 1, x + 1)) % MOD;
}
int main() {
  cin >> n >> m;
  fact[0] = 1;
  for (i64 i = 1; i < N; ++i) fact[i] = fact[i - 1] * i % MOD;
  i64 x = n + m + 1, y = n;
  cout << (c(x + y, y) + MOD - f(y - 1, x + 1) + MOD -
           g(y + m + 2, x - m - 2)) %
            MOD
       << '\n';
  return 0;
}
