#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (decltype(l + r) i = l; i <= r; ++i)
#define _divb(l, r, n, expressions)                 \
  for (decltype(n) l = 2, r; l <= (n); l = r + 1) { \
    r = (n) / ((n) / l);                            \
    expressions;                                    \
  }
using i64 = long long;
const i64 N = 1e6 + 5, P = 105, MOD = 1e9 + 7, inv_2 = (MOD + 1) / 2;
bool vis[N];
int prime[N], phi[N], cnt_prime;
void init(int n = N - 1) {
  phi[1] = 1;
  _for(i, 2, n) {
    if (!vis[i]) phi[prime[++cnt_prime] = i] = i - 1;
    for (i64 j = 1; j <= cnt_prime && i * prime[j] <= n; ++j) {
      vis[i * prime[j]] = 1;
      phi[i * prime[j]] = prime[j] * phi[i];
      if (i % prime[j] == 0) break;
      phi[i * prime[j]] -= phi[i];
    }
  }
  _for(i, 2, n) phi[i] = (phi[i] + phi[i - 1]) % MOD;
}
map<i64, i64> sum_phi;
i64 get_sum(i64 n) {
  if (n < N) return phi[n];
  if (sum_phi[n]) return sum_phi[n];
  i64 ret = n % MOD * ((n + 1) % MOD) % MOD * inv_2 % MOD;
  _divb(l,
        r,
        n,
        ret = ((ret - (r - l + 1) * get_sum(n / l) % MOD) % MOD + MOD) % MOD);
  return sum_phi[n] = ret;
}
i64 ans, n;
bool vis_h[N][P];
i64 h[N][P];
void dfs(i64 now_x, i64 now_h, i64 idx_prime) {
  ans = (ans + now_h * get_sum(n / now_x) % MOD) % MOD;
  if (idx_prime > 1 && now_x > n / prime[idx_prime] / prime[idx_prime]) return;
  _for(i, idx_prime, cnt_prime) {
    if (i > 1 && now_x > n / prime[i] / prime[i]) break;
    for (i64 now_exp = 1, next_x = now_x * prime[i]; next_x <= n;
         ++now_exp, next_x *= prime[i]) {
      if (!vis_h[i][now_exp]) {
        i64 f = prime[i] ^ now_exp, g = prime[i] - 1;
        _for(j, 1, now_exp) {
          f = ((f - g % MOD * h[i][now_exp - j] % MOD) % MOD + MOD) % MOD;
          (g *= prime[i]) %= MOD;
        }
        h[i][now_exp] = f;
        vis_h[i][now_exp] = 1;
      }
      if (h[i][now_exp]) dfs(next_x, h[i][now_exp] * now_h % MOD, i + 1);
    }
  }
}
int main() {
  init();
  cin >> n;
  _for(i, 1, cnt_prime) h[i][0] = 1;
  dfs(1, 1, 1);
  cout << ans;
  return 0;
}
