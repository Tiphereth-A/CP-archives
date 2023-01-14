#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
const int MOD = 1000000007;
bool vis[M];
int prime[M];
int cnt_p;
void init_prime(int n = M - 1) {
  _for(i, 2, n) {
    if (!vis[i]) vis[prime[++cnt_p] = i] = 1;
    for (int j = 1; j <= cnt_p && i * prime[j] <= n; ++j) {
      vis[i * prime[j]] = 1;
      if (i % prime[j] == 0) break;
    }
  }
}
i64 qpow(i64 a, i64 b) {
  a %= MOD;
  i64 res = 1;
  for (; b; b >>= 1, a = a * a % MOD)
    if (b & 1) res = res * a % MOD;
  return res;
}
int cnts[M * M];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  init_prime();
  int n;
  cin >> n;
  map<int, int> cnts;
  int maxa = 0;
  _for(i, 1, n, a) {
    cin >> a;
    maxa = max(maxa, a);
    _for(i, 1, cnt_p, sqrt_a = sqrt(a), cnt) {
      if (prime[i] > sqrt_a) break;
      if (a % prime[i] == 0) {
        cnt = 0;
        while (a % prime[i] == 0) {
          ++cnt;
          a /= prime[i];
        }
        cnts[prime[i]] += cnt % 2;
      }
    }
    if (a > 1) ++cnts[a];
  }
  i64 ans = 1;
  _for(i, 2, maxa)
    if (cnts[i]) ans = ans * qpow(i, min(cnts[i], n - cnts[i])) % MOD;
  cout << ans;
  return 0;
}
