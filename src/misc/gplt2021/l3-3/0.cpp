#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using i128 = __int128_t;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
const int N = 1.35e7 + 5;
map<i64, i128> sum_mu;
bool vis[N];
int prime[N], mu[N], cnt_prime;
i128 inv(i128 a, i128 mod) {
  i128 res = 1, b = mod - 2;
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
i128 get_sum_mu(i64 n, i64 p) {
  if (n < N) return mu[n];
  if (sum_mu[n]) return sum_mu[n];
  i128 ans = 1;
  for (i64 l = 2, r; l <= n; l = r + 1) {
    r = n / (n / l);
    ((ans -= (r - l + 1) * get_sum_mu(n / l, p) % p) += p) %= p;
  }
  return sum_mu[n] = ans;
}
int main() {
  i64 n, p = 1e9 + 7;
  cin >> n >> p;
  mu[1] = 1;
  _for(i, 2, N - 1) {
    if (!vis[i]) mu[prime[++cnt_prime] = i] = -1;
    for (int j = 1; j <= cnt_prime && i * prime[j] < N; ++j) {
      vis[i * prime[j]] = 1;
      if (i % prime[j] == 0) break;
      mu[i * prime[j]] = -mu[i];
    }
  }
  _for(i, 2, N - 1) (mu[i] += mu[i - 1]) %= p;
  i128 ans = 0;
  get_sum_mu(n, p);
  for (i128 l = 2, r, pre = get_sum_mu(1, p), now; l <= n; l = r + 1) {
    r = n / (n / l);
    (ans += (((now = get_sum_mu(r, p)) - pre) % p + p) % p * (n / l) % p *
            inv(n - n / l, p) % p) %= p;
    pre = now;
  }
  cout << ((i64)(1 - ans) % p + p) % p;
  return 0;
}
