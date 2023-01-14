#include <cstdio>
#include <cstring>
using namespace std;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
#define _rfor(i, r, l) for (decltype(l + r) i = (r); i >= (l); --i)
#define _set_nul(a) memset(a, 0, sizeof(a))
#define _set_nul_n(a, n) memset(a, 0, sizeof(a[0]) * (n))
const int OFFSET = 5;
const int N = 4e4 + OFFSET, M = 8e4 + OFFSET, K = 21;
struct Edge {
  i64 w;
  int to, next;
} e[M];
int head[N], cnt_edge;
void addEdge(int x, int y, i64 w = 1) {
  e[++cnt_edge] = {w, y, head[x]};
  head[x] = cnt_edge;
}
int f[K][N], dep[N], lg[N];
i64 sum[N];
void dfs(int x, int fa, i64 w = 0) {
  dep[x] = dep[f[0][x] = fa] + 1;
  sum[x] = sum[fa] + w;
  for (int i = 1; (1 << i) <= dep[x]; ++i) f[i][x] = f[i - 1][f[i - 1][x]];
  for (int i = head[x]; i; i = e[i].next)
    if (e[i].to != fa) dfs(e[i].to, x, e[i].w);
}
int lca(int x, int y) {
  if (dep[x] < dep[y]) x ^= y ^= x ^= y;
  while (dep[x] > dep[y]) x = f[lg[dep[x] - dep[y]] - 1][x];
  if (x == y) return x;
  _rfor(i, lg[dep[x]], 0)
    if (f[i][x] != f[i][y]) {
      x = f[i][x];
      y = f[i][y];
    }
  return f[0][x];
}
int main() {
  _for(i, 1, N - 1) lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
  int kase;
  scanf("%d", &kase);
  while (kase--) {
    int n, m;
    scanf("%d%d", &n, &m);
    int x, y;
    i64 z;
    _for(i, 1, n - 1) {
      scanf("%d%d%lld", &x, &y, &z);
      addEdge(x, y, z);
      addEdge(y, x, z);
    }
    dfs(1, 0);
    _for(i, 1, m) {
      scanf("%d%d", &x, &y);
      printf("%lld\n", sum[x] + sum[y] - 2 * sum[lca(x, y)]);
    }
  __end_kase:;
    _set_nul_n(head, n);
    _set_nul_n(dep, n);
    _set_nul_n(sum, n);
    _set_nul(f);
    cnt_edge = 0;
  }
  return 0;
}
