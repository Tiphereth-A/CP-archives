#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (auto i = (l); i <= (r); ++i)
const int OFFSET = 5;
const int N = 5e6 + OFFSET;
map<i64, i64> sum_mu;
bool vis[N];
int prime[N], mu[N], cnt_prime;
void init_prime(int p, int n = N - 1) {
  for (int i = 2; i <= n; ++i) {
    if (!vis[i]) mu[prime[++cnt_prime] = i] = -1;
    for (int j = 1; j <= cnt_prime && i * prime[j] <= n; ++j) {
      vis[i * prime[j]] = 1;
      if (i % prime[j] == 0) break;
      mu[i * prime[j]] = -mu[i];
    }
  }
  _for(i, 2, n) (mu[i] += mu[i - 1]) %= p;
}
i64 inv(i64 a, i64 mod) {
  i64 res = 1, b = mod - 2;
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
i64 get_sum_mu(i64 n, i64 p) {
  if (n < N) return mu[n];
  if (sum_mu[n]) return sum_mu[n];
  i64 ans = 1;
  for (i64 l = 2, r; l <= n; l = r + 1) {
    r = n / (n / l);
    ((ans -= (r - l + 1) * get_sum_mu(n / l, p) % p) += p) %= p;
  }
  return sum_mu[n] = ans;
}
int main() {
  i64 n, p = 1e9 + 7;
  cin >> n;
  init_prime(p);
  i64 ans = 0;
  for (i64 l = 2, r; l <= n; l = r + 1) {
    r = n / (n / l);
    (ans += ((get_sum_mu(r, p) - get_sum_mu(l - 1, p)) % p + p) % p * (n / l) %
            p * inv(n - n / l, p) % p) %= p;
  }
  cout << ((1 - ans) % p + p) % p;
  return 0;
}
