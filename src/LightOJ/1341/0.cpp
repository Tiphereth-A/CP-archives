#include <cstdio>
const int N = 1e6 + 5;
int pri[N], cnt_pri;
bool vis[N];
int main() {
  for (int i = 2; i < N; ++i)
    if (!vis[i]) {
      pri[++cnt_pri] = i;
      for (int j = 2; i * j < N; ++j) vis[i * j] = 1;
    }
  int kase;
  scanf("%d", &kase);
  for (int cnt = 1; cnt <= kase; ++cnt) {
    i64 area, a;
    scanf("%lld%lld", &area, &a);
    if (area < a * a) {
      printf("Case %d: 0\n", cnt);
      continue;
    }
    i64 n = area, sum = 1;
    for (i64 i = 1, ans; i <= cnt_pri && pri[i] * pri[i] <= n; ++i) {
      if (!(n % pri[i])) {
        ans = 0;
        while (!(n % pri[i])) {
          ++ans;
          n /= pri[i];
        }
        sum *= ans + 1;
      }
    }
    sum >>= n <= 1;
    for (i64 i = 1; i < a; ++i)
      if (!(area % i)) sum--;
    printf("Case %d: %lld\n", cnt, sum);
  }
  return 0;
}
