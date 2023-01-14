#include <bits/stdc++.h>
using namespace std;
typedef __int128_t i128;
const i64 MOD = 1e6 + 3;
int main() {
  i64 n;
  cin >> n;
  i64 ans = (i128)n % MOD * (n + 1) % MOD * 500002 % MOD, ans2 = 0;
  for (i64 a = 1, _ = __builtin_popcountll(n); n; (a *= 3) %= MOD, n >>= 1)
    if (n & 1) (ans2 += a * (((i128)1 << --_) % MOD) % MOD) %= MOD;
  cout << (ans - ans2 + MOD) % MOD << endl;
  return 0;
}
