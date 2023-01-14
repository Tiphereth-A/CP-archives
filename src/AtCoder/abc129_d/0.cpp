#include <bits/stdc++.h>
using namespace std;
const int OFFSET = 5, N = 2e3 + OFFSET, M = 8e6 + OFFSET;
char maps[N][N];
int cnt, num[M], idxa[N][N], idxb[N][N];
int main() {
  int h, w;
  scanf("%d%d\n", &h, &w);
  for (int i = 1; i <= h; ++i) scanf("%s", maps[i] + 1);
  for (int i = 1, now; i <= h; ++i) {
    now = 0;
    for (int j = 1; j <= w; ++j)
      if (maps[i][j] == '#') {
        num[cnt++] = now;
        now = 0;
      } else {
        idxa[i][j] = cnt;
        ++now;
      }
    if (now) num[cnt++] = now;
  }
  for (int j = 1, now; j <= w; ++j) {
    now = 0;
    for (int i = 1; i <= h; ++i)
      if (maps[i][j] == '#') {
        num[cnt++] = now;
        now = 0;
      } else {
        idxb[i][j] = cnt;
        ++now;
      }
    if (now) num[cnt++] = now;
  }
  int ans = 0;
  for (int i = 1; i <= h; ++i)
    for (int j = 1; j <= w; ++j)
      ans = max(ans, num[idxa[i][j]] + num[idxb[i][j]] - 1);
  printf("%d\n", ans);
  return 0;
}
