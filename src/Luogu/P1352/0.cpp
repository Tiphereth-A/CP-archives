#include <bits/stdc++.h>
const int N = 6e4 + 5;
struct edge {
  int next, to;
} e[N * 2];
int head[N], cnt_edge;
void add_edge(int u, int v) {
  e[++cnt_edge] = {head[u], v};
  head[u] = cnt_edge;
}
int n, root, r[N], f[N][2];
bool son[N];
int max(int a, int b) { return a > b ? a : b; }
void dfs(int x) {
  f[x][0] = 0;
  f[x][1] = r[x];
  for (int v, i = head[x]; i; i = e[i].next) {
    v = e[i].to;
    dfs(v);
    f[x][0] += max(f[v][0], f[v][1]);
    f[x][1] += f[v][0];
  }
}
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) scanf("%d", r + i);
  for (int k, l, i = 1; i < n; ++i) {
    scanf("%d%d", &l, &k);
    add_edge(k, l);
    son[l] = true;
  }
  for (int i = 1; i <= n; ++i)
    if (!son[i]) {
      root = i;
      break;
    }
  dfs(root);
  printf("%d", max(f[root][0], f[root][1]));
}
