#include <bits/stdc++.h>
using namespace std;
using u32 = unsigned;
const int N = 2e7 + 5;
u32 qpow(u32 a, u32 b) {
  u32 res = 1;
  for (; b; b >>= 1, a *= a)
    if (b & 1) res *= a;
  return res;
}
int prime[N / 10], cnt;
bool vis[N];
u32 sf[N], sik[N];
void seive(int n, u32 k) {
  sf[1] = sik[1] = 1;
  for (int i = 2; i <= n; ++i) {
    if (!vis[i]) {
      prime[++cnt] = i;
      sf[i] = i - 1;
      sik[i] = qpow(i, k);
    }
    for (int j = 1; j <= cnt && i * prime[j] <= n; ++j) {
      vis[i * prime[j]] = 1;
      sik[i * prime[j]] = sik[i] * sik[prime[j]];
      sf[i * prime[j]] = sf[i] * (prime[j] - 1);
      if (i % prime[j] == 0) {
        sf[i * prime[j]] =
          (i / prime[j] % prime[j]) ? -prime[j] * sf[i / prime[j]] : 0;
        break;
      }
    }
  }
  for (int i = 2; i <= n; ++i) {
    sf[i] = sf[i - 1] + sik[i] * sf[i];
    sik[i] += sik[i - 1];
  }
  for (int i = 2; i <= n; ++i) sik[i] += sik[i - 1];
}
u32 s(int n) { return sik[n * 2] - 2 * sik[n]; }
int main() {
  int _t, n;
  u32 k;
  scanf("%d%d%u", &_t, &n, &k);
  k - 1;
  seive(min(n * 2, N - 5), k);
  while (_t--) {
    scanf("%d", &n);
    u32 ans = 0;
    for (int l = 1, r; l <= n; l = r + 1) {
      r = n / (n / l);
      ans += (sf[r] - sf[l - 1]) * s(n / l);
    }
    printf("%u\n", ans);
  }
}
