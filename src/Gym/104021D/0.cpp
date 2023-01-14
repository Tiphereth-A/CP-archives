#include <bits/stdc++.h>
using ll = long long;
using i64 = ll;
template <class Tp>
using vc = std::vector<Tp>;
#define for_(i, l, r, v...) for (ll i = (l), i##e = (r), ##v; i <= i##e; ++i)
using namespace std;
const int N = 1e5 + 5;
int prime[N], cnt_prime;
bool vis[N];
int mu[N];
void init_prime(int n = N - 1) {
  mu[1] = 1;
  for_(i, 2, n) {
    if (!vis[i]) {
      prime[++cnt_prime] = i;
      mu[i] = -1;
    }
    for (int j = 1; j <= cnt_prime && i * prime[j] <= n; ++j) {
      vis[i * prime[j]] = 1;
      if (i % prime[j] == 0) continue;
      mu[i * prime[j]] = -mu[i];
    }
  }
}
const int MOD = 59964251, PHI = 642 * 93256;
constexpr i64 qpow(i64 a, i64 b, i64 mod) {
  i64 res = 1;
  a %= MOD;
  for (; b; b >>= 1, a = a * a % mod)
    if (b & 1) res = res * a % MOD;
  return res;
}
void solve(int t_ = 0) {
  int n = 0, m, d, k;
  string s;
  cin >> s;
  for (char ch : s) ((n *= 10) += ch - '0') %= PHI;
  cin >> m >> d >> k;
  i64 mm = m / d, nk = (i64)n * k % PHI;
  vc<i64> smue(mm + 1);
  for_(i, 1, mm)
    smue[i] =
      (smue[i - 1] + ((mu[i] * qpow(i, nk, MOD) % MOD) + MOD) % MOD) % MOD;
  vc<i64> si(mm + 1);
  for_(i, 1, mm) si[i] = (si[i - 1] + qpow(i, k, MOD)) % MOD;
  i64 ans = 0;
  for (i64 l = 1, r; l <= mm; l = r + 1) {
    r = mm / (mm / l);
    i64 __ = qpow(si[mm / l], n, MOD);
    (ans += (smue[r] + MOD - smue[l - 1]) % MOD * __ % MOD) %= MOD;
  }
  (ans *= qpow(d, nk, MOD)) %= MOD;
  cout << ans << '\n';
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  init_prime();
  int t_ = 0;
  std::cin >> t_;
  for (i_ = 0; i_ < t_; ++i_) solve(i_);
  return 0;
}
