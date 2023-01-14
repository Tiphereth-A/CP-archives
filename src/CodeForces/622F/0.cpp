#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int OFS = 5;
const int N = 1e6 + OFS, MOD = 1e9 + 7;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _rfor(i, r, l, vals...)                                      \
  for (make_signed_t<decltype(r - l)> i = (r), i##end = (l), ##vals; \
       i >= i##end;                                                  \
       --i)
constexpr i64 qpow(i64 a, i64 b = MOD - 2, const i64 &mod = MOD) {
  i64 res(1);
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
const int P = N / 10 + OFS;
int pri[P], cnt;
bool vis[N];
i64 pow_k[N];
void init_pow_k(int k) {
  pow_k[1] = 1;
  for (int i = 2; i <= k + 2; ++i) {
    if (!vis[i]) pow_k[i] = qpow(pri[++cnt] = i, k);
    for (int j = 1; j <= cnt && i * pri[j] <= k + 2; ++j) {
      vis[i * pri[j]] = 1;
      pow_k[i * pri[j]] = pow_k[i] * pow_k[pri[j]] % MOD;
      if (i % pri[j] == 0) break;
    }
  }
  _for(i, 1, k + 2)
    pow_k[i] = (pow_k[i] + pow_k[i - 1] > MOD ? pow_k[i] + pow_k[i - 1] - MOD :
                                                pow_k[i] + pow_k[i - 1]);
}
i64 pre[N], suc[N];
i64 fac[N], inv[N];
void init(const int k = N - OFS) {
  fac[0] = inv[0] = 1;
  _for(i, 1, k + 2) fac[i] = fac[i - 1] * i % MOD;
  inv[k + 2] = qpow(fac[k + 2]);
  _rfor(i, k + 1, 1) inv[i] = inv[i + 1] * (i + 1) % MOD;
}
init();
return 0;
}
();
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, k;
  cin >> n >> k;
  init_pow_k(k);
  if (n <= k + 2) {
    cout << pow_k[n] << '\n';
    return 0;
  }
  i64 ans = 0;
  pre[0] = suc[0] = suc[k + 3] = 1;
  _for(i, 1, k + 2) pre[i] = pre[i - 1] * (n - i) % MOD;
  _rfor(i, k + 2, 1) suc[i] = suc[i + 1] * (n - i) % MOD;
  _for(i, 1, k + 2) {
    auto a = pre[i - 1] * suc[i + 1] % MOD;
    auto b = inv[i - 1] *
             ((k - i) % 2 ? (MOD - inv[k + 2 - i]) : inv[k + 2 - i]) % MOD;
    ans = (ans + pow_k[i] * a % MOD * b % MOD) % MOD;
  }
  cout << ans << '\n';
  return 0;
}
