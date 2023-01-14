#include <cstdio>
const int N = 1e7 + 5, M = 1e6 + 5;
int pri[M], cnt_pri;
bool vis[N];
int main() {
  for (int i = 2; i < N; ++i) {
    if (!vis[i]) pri[++cnt_pri] = i;
    for (int j = 1; j <= cnt_pri && pri[j] * i < N; ++j) {
      vis[pri[j] * i] = 1;
      if (!(i % pri[j])) break;
    }
  }
  int kase;
  scanf("%d", &kase);
  for (int cnt = 1, n, sum; cnt <= kase; ++cnt) {
    sum = 0;
    scanf("%d", &n);
    for (int i = 1; pri[i] <= n / 2; ++i) sum += !vis[n - pri[i]];
    printf("Case %d: %d\n", cnt, sum);
  }
  return 0;
}
