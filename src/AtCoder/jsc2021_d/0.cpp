#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int MOD = 1e9 + 7;
i64 qpow(i64 a, i64 b, i64 mod = MOD) {
  i64 res = 1;
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
int main() {
  i64 n, p;
  cin >> n >> p;
  cout << (p - 1) * qpow(p - 2, n - 1) % MOD;
  return 0;
}
