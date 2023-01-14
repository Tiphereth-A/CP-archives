#include <bits/stdc++.h>
using namespace std;
#define re
const int N = 3010;
int n, m, mp[N][N], vi[N], tot = 1;
int main() {
  scanf("%d%d", &n, &m);
  for (re int i = 1; i <= m; i++) {
    int o, p;
    scanf("%d%d", &o, &p);
    mp[o][p] = 1, mp[p][o] = 1;
  }
  for (re int i = 1; i <= n; i++) {
    if (vi[i]) continue;
    for (re int j = i + 1; j <= n; j++) {
      if (vi[j] || mp[i][j]) continue;
      vi[i] = 1, vi[j] = 1;
      break;
    }
  }
  for (re int i = 1; i <= n; i++) {
    if (tot * 3 > n) break;
    if (vi[i]) continue;
    printf("%d ", i);
    tot++;
  }
  printf("\n");
  return 0;
}
