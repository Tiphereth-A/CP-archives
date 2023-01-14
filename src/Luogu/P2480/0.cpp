#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
const int N = 3.6e4, K = 4;
const int MOD = 999911659, mods[K] = {2, 3, 4679, 35617};
i64 frac[K][N] = {{1}, {1}, {1}, {1}}, inv[K][N];
map<pii, i64> comb[4];
i64 c(int m, int n, int k) {
  if (comb[k].count(make_pair(m, n))) return comb[k][make_pair(m, n)];
  if (n > m) return comb[k][make_pair(m, n)] = 0;
  if (m == n || n == 0) return comb[k][make_pair(m, n)] = 1;
  return comb[k][make_pair(m, n)] =
           frac[k][m] * inv[k][n] % mods[k] * inv[k][m - n] % mods[k];
}
i64 lucas(int m, int n, int k) {
  if (comb[k].count(make_pair(m, n))) return comb[k][make_pair(m, n)];
  if (n > m) return comb[k][make_pair(m, n)] = 0;
  if (m == n || n == 0) return comb[k][make_pair(m, n)] = 1;
  return comb[k][make_pair(m, n)] = 1ll * lucas(m / mods[k], n / mods[k], k) *
                                    c(m % mods[k], n % mods[k], k) % mods[k];
}
i64 qpow(i64 a, i64 b, int mod = MOD) {
  i64 res = 1;
  a %= mod;
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
void init_frac_inv() {
  for (int k = 0; k < 4; ++k)
    for (int i = 1; i <= mods[k]; ++i)
      frac[k][i] = frac[k][i - 1] * i % mods[k];
  for (int k = 0; k < 4; ++k)
    for (int i = 1; i <= mods[k]; ++i)
      inv[k][i] = qpow(frac[k][i], mods[k] - 2, mods[k]);
}
constexpr int a[K] = {
  499955829, 333303886, 213702 * 1353, 28074 * 31254 % (MOD - 1)};
int n, g;
i64 calc_comb_crt(i64 d) {
  return ((lucas(n, d, 0) * a[0] % (MOD - 1) +
           lucas(n, d, 1) * a[1] % (MOD - 1)) %
            (MOD - 1) +
          (lucas(n, d, 2) * a[2] % (MOD - 1) +
           lucas(n, d, 3) * a[3] % (MOD - 1)) %
            (MOD - 1)) %
         (MOD - 1);
}
int main() {
  cin >> n >> g;
  if ((g %= MOD) == 0) {
    cout << 0;
    return 0;
  }
  if (g == 1) {
    cout << 1;
    return 0;
  }
  i64 exp = 0;
  init_frac_inv();
  for (int i = 1; i * i <= n; ++i)
    if (n % i == 0) {
      (exp += calc_comb_crt(i)) %= MOD - 1;
      if (i != n / i) (exp += calc_comb_crt(n / i)) %= MOD - 1;
    }
  cout << qpow(g, exp);
  return 0;
}
