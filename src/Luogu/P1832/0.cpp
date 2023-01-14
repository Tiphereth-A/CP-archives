#include <bits/stdc++.h>
#define N 10005
typedef long long ll;
ll n, cnt;
ll prime[N], f[N] = {1};
bool vis[N];
void GetPrime() {
  for (ll i = 2; i <= n; ++i) {
    if (!vis[i]) prime[++cnt] = i;
    for (ll j = 1; j <= cnt && i * prime[j] <= n; ++j) {
      vis[i * prime[j]] = 1;
      if (!(i % prime[j])) break;
    }
  }
}
int main() {
  scanf("%lld", &n);
  GetPrime();
  for (ll i = 1; i <= cnt; ++i) {
    int tmp = prime[i];
    for (ll j = tmp; j <= n; ++j) f[j] += f[j - tmp];
  }
  printf("%lld", f[n]);
  return 0;
}
