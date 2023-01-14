#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const i64 MOD = 998244353;
i64 calc(i64 n) {
  i64 ans = 0;
  for (i64 l = 1, r; l <= n; l = r + 1)
    ans += ((r = n / (n / l)) - l + 1) * (n / l) % MOD;
  return ans % MOD;
}
int main() {
  i64 l, r;
  cin >> l >> r;
  cout << (calc(r) + MOD - calc(l - 1)) % MOD;
  return 0;
}
