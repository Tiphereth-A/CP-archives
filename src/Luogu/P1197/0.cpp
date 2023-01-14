#include <bits/stdc++.h>
const int M = 4e5 + 5;
int n, m, fa[M], tar[M];
struct edge {
  int from, next, to;
} e[M];
int head[M], cnt, ans[M], tot;
bool broken[M];
void add(int u, int v) {
  e[++cnt] = {u, head[u], v};
  head[u] = cnt;
}
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) {
  int fx = find(x), fy = find(y);
  if (fx != fy) {
    fa[fy] = fx;
    --tot;
  }
}
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) fa[i] = i;
  int u, v;
  for (int i = 0; i < m; ++i) {
    scanf("%d%d", &u, &v);
    add(u, v);
    add(v, u);
  }
  scanf("%d", &u);
  for (int i = 1; i <= u; ++i) {
    scanf("%d", &v);
    broken[tar[i] = v] = 1;
  }
  tot = n - u;
  for (int i = 1; i <= m * 2; i += 2)
    if (!broken[e[i].from] && !broken[e[i].to]) merge(e[i].from, e[i].to);
  ans[u + 1] = tot;
  for (int i = u; i; --i) {
    int now = tar[i];
    ++tot;
    broken[now] = 0;
    for (int j = head[now]; j; j = e[j].next) {
      if (!broken[e[j].to]) merge(now, e[j].to);
    }
    ans[i] = tot;
  }
  for (int i = 1; i <= u + 1; ++i) printf("%d\n", ans[i]);
  return 0;
}
