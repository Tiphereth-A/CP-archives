#include <cstdio>
const int N = 1e6 + 5;
bool vis[N], is_pri[N];
int pri[N], cnt;
bool f[N];
long long sum[N];
int main() {
  for (int i = 2; i < N; ++i) {
    if (!vis[i]) {
      vis[i] = is_pri[i] = 1;
      pri[++cnt] = i;
      for (long long j = 2; j * i < N; ++j) vis[j * i] = 1;
    }
  }
  for (int i = 1, _, tot; i <= cnt; ++i) {
    tot = 0;
    _ = pri[i];
    while (_) {
      tot += _ % 10;
      _ /= 10;
    }
    if (is_pri[tot]) f[pri[i]] = 1;
  }
  for (int i = 2; i < N; ++i) sum[i] = sum[i - 1] + f[i];
  int n;
  scanf("%d", &n);
  for (int i = 1, a, b; i <= n; ++i) {
    scanf("%d%d", &a, &b);
    printf("%lld\n", sum[b] - sum[a - 1]);
  }
}
