#include <bits/stdc++.h>
using namespace std;
const int N = 2e6 + 5;
struct E {
  int to, next;
} e[N * 2];
int cnt_edge, head[N];
void addEdge(int u, int v) {
  e[++cnt_edge] = {v, head[u]};
  head[u] = cnt_edge;
}
int fa[22][N];
void dfs1(int u, int f) {
  fa[0][u] = f;
  for (int i = 1; i <= 21; ++i) fa[i][u] = fa[i - 1][fa[i - 1][u]];
  for (int i = head[u]; i; i = e[i].next) {
    int v = e[i].to;
    if (v == f) continue;
    dfs1(v, u);
  }
}
int d[N];
void dfs2(int u, int f) {
  for (int i = head[u], v; i; i = e[i].next) {
    if ((v = e[i].to) == f) continue;
    dfs2(v, u);
    d[u] += d[v];
  }
}
int main() {
  int n;
  cin >> n;
  for (int i = 1; i < n; ++i) {
    int u, v;
    cin >> u >> v;
    addEdge(u, v);
    addEdge(v, u);
  }
  dfs1(1, 1);
  for (int i = 1, x, u; i <= n; ++i) {
    cin >> x;
    u = i;
    for (int j = 21; x; --j)
      if (x >= (1 << j)) {
        x -= (1 << j);
        u = fa[j][u];
      }
    ++d[i];
    --d[u == 1 ? 0 : fa[0][u]];
  }
  dfs2(1, 0);
  for (int i = 1; i <= n; ++i) cout << d[i] << ' ';
  cout << '\n';
  return 0;
}
