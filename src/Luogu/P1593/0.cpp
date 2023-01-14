#include <bits/stdc++.h>
using namespace std;
const int MOD = 9901;
i64 qpow(i64 a, i64 b = MOD - 2, i64 mod = MOD) {
  i64 res = 1;
  a %= mod;
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
int main() {
  i64 a, b;
  cin >> a >> b;
  i64 ans = 1;
  for (int i = 2; i <= sqrt(a); ++i)
    if (a % i == 0) {
      i64 cnt = 0;
      while (a % i == 0) {
        ++cnt;
        a /= i;
      }
      cnt *= b;
      (ans *=
       ((i % MOD == 1) ? cnt + 1 :
                         (qpow(i, cnt + 1) + MOD - 1) % MOD * qpow(i - 1)) %
       MOD) %= MOD;
    }
  if (a > 1)
    (ans *=
     ((a % MOD == 1) ? b + 1 : (qpow(a, b + 1) + MOD - 1) % MOD * qpow(a - 1)) %
     MOD) %= MOD;
  cout << ans;
  return 0;
}
