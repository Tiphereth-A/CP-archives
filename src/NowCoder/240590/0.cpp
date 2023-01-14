#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int N = 8000 + 5;
const int MOD = 998244353;
constexpr i64 qpow(i64 a, i64 b = MOD - 2, const i64 &mod = MOD) {
  i64 res(1);
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
};
i64 a[N], inv_a[N];
int prob[N][N], s[N][N];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  i64 n;
  cin >> n;
  for (int i = 1; i < n; ++i) cin >> a[i];
  {
    static i64 pa[N];
    pa[0] = 1;
    for (int i = 1; i < n; ++i) pa[i] = pa[i - 1] * a[i] % MOD;
    i64 _ = qpow(pa[n - 1]);
    for (int i = n - 1; i; --i) {
      inv_a[i] = _ * pa[i - 1] % MOD;
      _ = _ * a[i] % MOD;
    }
  }
  prob[n][0] = s[n][0] = 1;
  for (int i = n - 1; i; --i) {
    s[i][0] = s[i + 1][0];
    for (int j = 1; j <= n - i; ++j) {
      prob[i][j] =
        inv_a[i] * (s[i + 1][j - 1] + MOD - s[i + a[i] + 1][j - 1]) % MOD;
      s[i][j] = (s[i + 1][j] + prob[i][j]) % MOD;
    }
  }
  i64 ans = 0;
  for (int i = 1; i <= n; ++i)
    (ans += (i64)prob[1][i] * prob[1][i] % MOD) % MOD;
  cout << ans % MOD;
  return 0;
}
