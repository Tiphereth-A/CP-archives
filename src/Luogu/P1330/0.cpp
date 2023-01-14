#include <bits/stdc++.h>
using namespace std;
struct Edge {
  int t;
  int nexty;
} edge[200005];
int head[20005];
int cnt;
void add(int a, int b) {
  edge[++cnt].t = b;
  edge[cnt].nexty = head[a];
  head[a] = cnt;
}
bool used[20005];
int col[20005];
int sum[2];
bool dfs(int node, int color) {
  if (used[node]) {
    if (col[node] == color) return true;
    return false;
  }
  used[node] = true;
  sum[col[node] = color]++;
  bool tf = true;
  for (int i = head[node]; i != 0 && tf; i = edge[i].nexty) {
    tf = tf && dfs(edge[i].t, 1 - color);
  }
  return tf;
}
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  int a, b;
  while (m--) {
    scanf("%d%d", &a, &b);
    add(a, b);
    add(b, a);
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    if (used[i]) continue;
    sum[0] = sum[1] = 0;
    if (!dfs(i, 0)) {
      printf("Impossible");
      return 0;
    }
    ans += min(sum[0], sum[1]);
  }
  printf("%d", ans);
  return 0;
}
