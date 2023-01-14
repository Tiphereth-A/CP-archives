#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (i64 i = (l), i##end = (r), ##vals; i <= i##end; ++i)
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
const i64 MOD = 1e9 + 7, INV2 = 5e8 + 4;
constexpr i64 qpow(i64 a, i64 b = MOD - 2, const i64 &mod = MOD) {
  i64 res(1);
  a %= mod;
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
};
const int N = 2e5 + 5, P = 2e5 + 5;
bool vis[N];
i64 prime[P], cnt_prime;
i64 invp2[P], f[N];
void init_prime(const i64 &n = N - 1) {
  f[1] = 1;
  for (i64 i = 2; i <= n; ++i) {
    if (!vis[i]) {
      prime[++cnt_prime] = i;
      invp2[cnt_prime] = qpow(i * i);
      f[i] = (invp2[cnt_prime] + MOD - 1) % MOD;
    }
    for (i64 j = 1; j <= cnt_prime && i * prime[j] <= n; ++j) {
      vis[i * prime[j]] = 1;
      if (i % prime[j] == 0) {
        f[i * prime[j]] = (MOD - f[i] * invp2[j] % MOD + 1) % MOD;
        break;
      }
      f[i * prime[j]] = f[i] * f[prime[j]] % MOD;
    }
  }
}
i64 a[N], g[N];
auto solve() -> void {
  i64 n;
  cin >> n;
  i64 max_num = 0;
  _for(i, 1, n, x, y, cnt) {
    cin >> x;
    y = 1;
    _for(j, 1, cnt_prime) {
      if (prime[j] > sqrt(x)) break;
      if (x % prime[j]) continue;
      cnt = 0;
      while (x % prime[j] == 0) {
        ++cnt;
        x /= prime[j];
      }
      if (cnt & 1) y *= prime[j];
    }
    chkmax(max_num, x * y);
    ++a[x * y];
  }
  _for(i, 1, max_num)
    for (i64 j = 1; i * j <= max_num; ++j)
      (g[i] += i * j % MOD * a[i * j] % MOD) %= MOD;
  _for(i, 1, max_num) g[i] = g[i] * g[i] % MOD;
  i64 ans = 0;
  _for(i, 1, max_num) (ans += f[i] * g[i] % MOD) %= MOD;
  cout << (ans + MOD - n) % MOD * INV2 % MOD;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  init_prime();
  solve();
  return 0;
}
