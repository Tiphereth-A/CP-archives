#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int MOD = 1e5 + 3;
i64 qpow(i64 a, i64 b, i64 mod = MOD) {
  i64 res = 1;
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
int main() {
  i64 m, n;
  cin >> m >> n;
  cout << (qpow(m, n) - qpow(m - 1, n - 1) * m % MOD + MOD) % MOD;
  return 0;
}
