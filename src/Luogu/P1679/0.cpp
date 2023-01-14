#include <bits/stdc++.h>
#define N 100005
#define ll int
int n, cnt, list[20] = {0, 1}, f[N];
ll min(ll a, ll b) { return a > b ? b : a; }
int main() {
  scanf("%d", &n);
  cnt = ceil(sqrt(sqrt(n)) + 1);
  for (int i = 2; i <= cnt; ++i) list[i] = i * i * i * i;
  memset(f + 1, 0x3f, sizeof(f) - sizeof(int));
  for (ll i = 1; i <= cnt; ++i) {
    int tmp = list[i];
    for (ll j = tmp; j <= n; ++j) f[j] = min(f[j], f[j - tmp] + 1);
  }
  printf("%d", f[n]);
  return 0;
}
