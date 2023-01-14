#include <cstdio>
#define N 1010
int n, ans[N], gus[N], cnt;
int min(int a, int b) { return a < b ? a : b; }
int main() {
  while (scanf("%d", &n) == 1 && n) {
    int cnta[10] = {0};
    printf("Game %d:\n", ++cnt);
    for (int i = 1; i <= n; ++i) {
      scanf("%d", ans + i);
      ++cnta[ans[i]];
    }
    while (1) {
      int cntg[10] = {0}, a = 0, b = 0;
      for (int i = 1; i <= n; ++i) {
        scanf("%d", gus + i);
        if (ans[i] == gus[i]) ++a;
        ++cntg[gus[i]];
      }
      if (!gus[1]) break;
      for (int i = 1; i <= 9; ++i) b += min(cnta[i], cntg[i]);
      printf("    (%d,%d)\n", a, b - a);
    }
  }
  return 0;
}
