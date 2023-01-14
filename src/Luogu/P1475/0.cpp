#include <bits/stdc++.h>
using namespace std;
int a[102][102];
int cnt[102];
int m;
bool f[102];
bool vis[102];
void ff(int x) {
  if (f[x] == 1) return;
  f[x] = 1;
  for (int i = m; i; i--) {
    cnt[i] += a[x][i];
    if (cnt[i] > 50) {
      vis[i] = 1;
      ff(i);
    }
  }
}
int main() {
  int u, v, w, n;
  for (scanf("%d", &n); n; n--) {
    scanf("%d%d%d", &u, &v, &w);
    a[u][v] = w;
    m = max({u, m, v});
  }
  for (int i = 1; i <= m; i++) {
    memset(f, 0, sizeof(f));
    memset(vis, 0, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    ff(i);
    for (int j = 1; j <= m; j++)
      if (vis[j] == true && i != j) printf("%d %d\n", i, j);
  }
  return 0;
}
