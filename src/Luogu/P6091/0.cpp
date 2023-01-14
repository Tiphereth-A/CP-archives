#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int phi[N];
int prime[N / 10], cnt_prime;
bool vis[N];
int pri_root[N], cnt_priroot;
bool has_priroot[N];
int factor[N], cnt_factor;
int qpow(i64 a, int b, int mod) {
  i64 res = 1;
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
int main() {
  for (int i = 2; i < N; ++i) {
    if (!vis[i]) {
      prime[++cnt_prime] = i;
      phi[i] = i - 1;
      for (long long j = i; j < N; j *= i)
        has_priroot[j] = has_priroot[j * 2] = 1;
    }
    for (int j = 1; j <= cnt_prime && i * prime[j] < N; ++j) {
      vis[i * prime[j]] = 1;
      phi[i * prime[j]] = phi[i] * prime[j];
      if (i % prime[j] == 0) break;
      phi[i * prime[j]] -= phi[i];
    }
  }
  int kase;
  cin >> kase;
  while (kase--) {
    int n, d;
    cin >> n >> d;
    cnt_priroot = cnt_factor = 0;
    if (!has_priroot[n]) {
      cout << 0 << endl << endl;
      continue;
    }
    for (int i = 1, _ = phi[n]; i <= cnt_prime && prime[i] <= _; ++i)
      if (_ % prime[i] == 0) {
        factor[++cnt_factor] = prime[i];
        while (_ % prime[i] == 0) _ /= prime[i];
      }
    int g = 0;
    for (int i = 1; i < n; ++i) {
      if (gcd(i, n) != 1) continue;
      for (int j = 1; j <= cnt_factor; ++j)
        if (qpow(i, phi[n] / factor[j], n) == 1) goto __end_g;
      g = i;
      break;
    __end_g:;
    }
    for (int i = 1; i <= phi[n]; ++i)
      if (gcd(i, phi[n]) == 1) pri_root[++cnt_priroot] = qpow(g, i, n);
    sort(pri_root + 1, pri_root + cnt_priroot + 1);
    cout << cnt_priroot << endl;
    for (int i = d; i <= cnt_priroot; i += d) cout << pri_root[i] << " ";
    cout << endl;
  }
  return 0;
}
