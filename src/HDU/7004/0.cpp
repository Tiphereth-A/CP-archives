#include <bits/stdc++.h>
using i64 = int64_t;
using namespace std;
i64 qpow(i64 a, i64 b, i64 mod) {
  i64 res(1);
  a %= mod;
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
const i64 MOD = 998244353;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t_ = 0;
  cin >> t_;
  while (t_--) {
    i64 a, b, k;
    cin >> a >> b >> k;
    i64 _ = qpow(2, k / 2, MOD);
    a = a * _ % MOD;
    b = b * _ % MOD;
    if (k & 1) {
      _ = (a + b) % MOD;
      b = (a + MOD - b) % MOD;
      a = _;
    }
    cout << a << ' ' << b << '\n';
  }
  return 0;
}
