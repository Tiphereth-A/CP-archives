#include <cmath>
#include <cstdio>
#include <cstring>
const int N = 1e4 + 5;
bool vis[N];
int pri[N], cnt_pri;
int mu[N] = {0, 1};
int a[N], num[N];
int main() {
  for (int i = 2; i < N; ++i) {
    if (!vis[i]) {
      pri[++cnt_pri] = i;
      mu[i] = -1;
    }
    for (int j = 1; j <= cnt_pri && i * pri[j] < N; ++j) {
      vis[i * pri[j]] = 1;
      if (i % pri[j]) mu[i * pri[j]] = -mu[i];
      else {
        mu[i * pri[j]] = 0;
        break;
      }
    }
  }
  int n;
  while (~scanf("%d", &n)) {
    memset(num, 0, sizeof(num));
    memset(a, 0, sizeof(a));
    int max = 0;
    for (int i = 1, _; i <= n; ++i) {
      scanf("%d", &_);
      ++a[_];
      max < _ ? max = _ : 0;
    }
    if (n < 4) {
      puts("0");
      continue;
    }
    for (int i = 1; i <= max; ++i)
      for (int j = i; j <= max; j += i) num[i] += a[j];
    long long ans = 0;
    for (int i = 1, _; i <= max; ++i)
      if ((_ = num[i]) > 3)
        ans += 1ll * mu[i] * _ * (_ - 1) / 2 * (_ - 2) / 3 * (_ - 3) / 4;
    printf("%lld\n", ans);
  }
}
