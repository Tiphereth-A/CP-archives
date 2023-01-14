#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int N = 2000 + 5;
const i64 MOD = 1e9 + 9;
int a[N], b[N];
i64 fact[N], c[N][N], f[N][N];
int main() {
  int n, k;
  cin >> n >> k;
  if ((n + k) % 2) {
    cout << "0\n";
    return 0;
  }
  for (int i = 1; i <= n; ++i) cin >> a[i];
  for (int i = 1; i <= n; ++i) cin >> b[i];
  sort(a + 1, a + n + 1);
  sort(b + 1, b + n + 1);
  for (int i = 0; i <= n; ++i) f[i][0] = 1;
  for (int i = 1, p = 1; i <= n; ++i) {
    while (p <= n && b[p] < a[i]) ++p;
    for (int j = 1; j <= n; ++j)
      f[i][j] = (f[i - 1][j] + f[i - 1][j - 1] * (p - j)) % MOD;
  }
  c[0][0] = fact[0] = 1;
  for (int i = 1; i <= n; ++i) fact[i] = fact[i - 1] * i % MOD;
  for (int i = 1; i <= n; ++i) {
    c[i][0] = 1;
    for (int j = 1; j <= i; ++j)
      c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % MOD;
  }
  i64 ans = 0;
  int m = (n + k) / 2;
  for (int i = m; i <= n; ++i)
    ans =
      (ans +
       ((i + m) % 2 ? -1 : 1) * c[i][m] * f[n][i] % MOD * fact[n - i] % MOD +
       MOD) %
      MOD;
  cout << ans << endl;
  return 0;
}
