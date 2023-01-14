#include <bits/stdc++.h>
using namespace std;
int n, m;
int head[3010], ceg;
int val[3010];
int dp[3010][3010];
struct node {
  int to, next, w;
} edge[10000010];
void addEdge(int u, int v, int w) {
  edge[++ceg].to = v;
  edge[ceg].next = head[u];
  edge[ceg].w = w;
  head[u] = ceg;
}
int dfs(int u) {
  if (u > n - m) {
    dp[u][1] = val[u];
    return 1;
  }
  int sum = 0, t;
  for (int ceg = head[u]; ceg; ceg = edge[ceg].next) {
    int v = edge[ceg].to;
    t = dfs(v);
    sum += t;
    for (int j = sum; j > 0; j--)
      for (int i = 1; i <= t; i++)
        if (j - i >= 0)
          dp[u][j] = max(dp[u][j], dp[u][j - i] + dp[v][i] - edge[ceg].w);
  }
  return sum;
}
int main() {
  memset(dp, ~0x3f, sizeof(dp));
  scanf("%d%d", &n, &m);
  for (int u = 1; u <= n - m; u++) {
    int size, v, w;
    scanf("%d", &size);
    for (int j = 1; j <= size; j++) {
      scanf("%d%d", &v, &w);
      addEdge(u, v, w);
    }
  }
  for (int i = n - m + 1; i <= n; i++) scanf("%d", &val[i]);
  for (int i = 1; i <= n; i++) dp[i][0] = 0;
  dfs(1);
  for (int i = m; i >= 1; i--)
    if (dp[1][i] >= 0) {
      printf("%d", i);
      break;
    }
  return 0;
}
