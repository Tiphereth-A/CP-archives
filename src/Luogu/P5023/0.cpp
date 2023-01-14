#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const i64 MOD = 1e9 + 7;
i64 qpow(i64 a, i64 b) {
  i64 ans = 1;
  for (; b; a = a * a % MOD, b >>= 1)
    if (b & 1) ans = ans * a % MOD;
  return ans;
}
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, m;
  cin >> n >> m;
  if (n > m) swap(n, m);
  if (n == 1) cout << qpow(2, m) << '\n';
  else if (n == 2) cout << 4 * qpow(3, m - 1) % MOD << '\n';
  else if (n == 3) cout << 112 * qpow(3, m - 3) % MOD << '\n';
  else if (n == m)
    cout << (83 * qpow(8, n) + 5 * qpow(2, n + 7)) % MOD * qpow(384, MOD - 2) %
              MOD
         << '\n';
  else
    cout << (83 * qpow(8, n) + qpow(2, n + 8)) % MOD * qpow(3, m - n - 1) %
              MOD * qpow(128, MOD - 2) % MOD
         << '\n';
  return 0;
}
