#include <bits/stdc++.h>
const i64 M = 2e6 + 5, N = 1e6 + 5;
const i64 MOD = 80112002;
struct edge {
  int to, next;
} e[M];
int head[N], cnt;
void addEdge(int u, int v) {
  e[++cnt] = {v, head[u]};
  head[u] = cnt;
}
int in[N], out[N];
i64 f[N];
i64 dfs(i64 pos) {
  if (f[pos]) return f[pos];
  if (in[pos] && !out[pos]) return f[pos] = 1;
  for (int i = head[pos]; i; i = e[i].next) (f[pos] += dfs(e[i].to)) %= MOD;
  return f[pos];
}
int main() {
  int n, m;
  scanf("%lld%lld", &n, &m);
  for (int i = 1, x, y; i <= m; ++i) {
    scanf("%lld%lld", &x, &y);
    addEdge(x, y);
    ++in[y];
    ++out[x];
  }
  i64 ans = 0;
  for (int i = 1; i <= n; ++i)
    if (!in[i]) (ans += dfs(i)) %= MOD;
  printf("%lld", ans);
  return 0;
}
