#include <bits/stdc++.h>
struct gar {
  int t, h, f;
} a[105];
int dp[105][1005];
int max(int a, int b) { return a > b ? a : b; }
bool cmp(gar a, gar b) { return (a.t == b.t) ? (a.h > b.h) : (a.t < b.t); }
int main() {
  int d, g;
  memset(dp, 0xff, sizeof(dp));
  int nowt = dp[0][0] = 10, pstt = 0;
  scanf("%d%d", &d, &g);
  for (int i = 1; i <= g; ++i) scanf("%d%d%d", &a[i].t, &a[i].f, &a[i].h);
  std::sort(a + 1, a + g + 1, cmp);
  for (int i = 0; i <= g; ++i)
    for (int j = 0; j <= d; ++j) {
      if (dp[i][j] < 0) continue;
      int tmp = dp[i][j], tmpt = a[i + 1].t - a[i].t;
      if (j + a[i + 1].h >= d && tmp >= tmpt) {
        printf("%d\n", a[i + 1].t);
        return 0;
      }
      if (tmp - tmpt + 1) {
        dp[i + 1][j + a[i + 1].h] = tmp - tmpt;
        dp[i + 1][j] = max(dp[i + 1][j], tmp - tmpt + a[i + 1].f);
      }
    }
  for (int i = 1; i <= g; ++i) {
    int tmp = a[i].t - a[i - 1].t;
    if (tmp > nowt) {
      printf("%d\n", nowt + pstt);
      return 0;
    }
    pstt += tmp;
    nowt += a[i].f - tmp;
  }
  printf("%d\n", nowt + pstt);
  return 0;
}
