#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define _rfor(i, r, l) for (int i = (r); i >= (l); --i)
#define _set_nul(a) memset(a, 0, sizeof(a))
#define _set_nul_n(a, n) memset(a, 0, sizeof(a[0]) * (n))
#define _I64_MAX 9223372036854775807ll
const int OFFSET = 5;
const int N = 1e4 + OFFSET, M = 1e5 + OFFSET, K = 15;
struct Edge {
  long long w;
  int from, to;
  Edge(long long _w = 0, int _from = 0, int _to = 0)
    : w(_w), from(_from), to(_to) {}
  bool operator<(const Edge &other) const { return w > other.w; }
} e[M];
int cnt_edge;
void addEdge(int x, int y, long long w = 1) { e[++cnt_edge] = Edge(w, x, y); }
struct Tree {
  long long w;
  int to, next;
  Tree(long long _w = 0, int _to = 0, int _next = 0)
    : w(_w), to(_to), next(_next) {}
} e_tr[M];
int head[N], cnt_tree;
void add_treeEdge(int x, int y, long long w = 1) {
  e_tr[++cnt_tree] = Tree(w, y, head[x]);
  head[x] = cnt_tree;
}
int fa[N];
int find(int x) { return x == fa[x] ? fa[x] : fa[x] = find(fa[x]); }
void merge(int x, int y) { fa[find(x)] = find(y); }
bool kruskal(int n, int k = 1) {
  sort(e + 1, e + cnt_edge + 1);
  for (int i = 0; i <= n; ++i) fa[i] = i;
  int cnt = 0;
  for (int i = 1, fx, fy; i <= cnt_edge; ++i) {
    fx = find(e[i].from);
    fy = find(e[i].to);
    if (fx == fy) continue;
    fa[fx] = fy;
    ++cnt;
    add_treeEdge(e[i].from, e[i].to, e[i].w);
    add_treeEdge(e[i].to, e[i].from, e[i].w);
    if (cnt == n - k) break;
  }
  return cnt == n - k;
}
int f[K][N], dep[N];
long long minw[K][N];
bool vis[N];
void dfs(int x) {
  vis[x] = 1;
  for (int i = head[x], to; i; i = e_tr[i].next)
    if (!vis[to = e_tr[i].to]) {
      dep[to] = dep[x] + 1;
      f[0][to] = x;
      minw[0][to] = e_tr[i].w;
      dfs(to);
    }
}
long long lca(int x, int y) {
  if (dep[x] < dep[y]) swap(x, y);
  long long ret = _I64_MAX;
  for (int i = 0, d = dep[x] - dep[y]; d; ++i, d >>= 1)
    if (d & 1) {
      ret = min(ret, minw[i][x]);
      x = f[i][x];
    }
  if (x == y) return ret;
  _rfor(i, K - 1, 0)
    if (f[i][x] != f[i][y]) {
      ret = min(ret, min(minw[i][x], minw[i][y]));
      x = f[i][x];
      y = f[i][y];
    }
  return min(ret, min(minw[0][x], minw[0][y]));
}
int main() {
  int kase;
  scanf("%d", &kase);
  _for(_k, 1, kase) {
    int n, m;
    scanf("%d%d", &n, &m);
    int x, y, z;
    _for(i, 1, m) {
      scanf("%d%d%d", &x, &y, &z);
      addEdge(x, y, z);
      addEdge(y, x, z);
    }
    kruskal(n);
    _for(i, 1, n)
      if (!vis[i]) {
        dep[i] = 1;
        f[0][i] = i;
        minw[0][i] = _I64_MAX;
        dfs(i);
      }
    _for(i, 1, K - 1)
      _for(x, 1, n) {
        f[i][x] = f[i - 1][f[i - 1][x]];
        minw[i][x] = min(minw[i - 1][x], minw[i - 1][f[i - 1][x]]);
      }
    printf("Scenario #%d:\n%lld\n", _k, lca(1, n));
  __end_kase:;
    cnt_edge = cnt_tree = 0;
    _set_nul_n(head, n + 1);
    _set_nul_n(vis, n + 1);
    _set_nul_n(dep, n + 1);
    _set_nul(f);
    _set_nul(minw);
    puts("");
  }
  return 0;
}
