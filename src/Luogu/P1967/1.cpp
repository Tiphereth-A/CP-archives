#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e4 + 5, M = 2e5 + 5, K = 21;
struct Edge {
  ll w;
  int from, to;
  bool operator<(const Edge &other) const { return w > other.w; }
} e[M];
int cnt_edge;
void addEdge(int x, int y, ll w = 1) { e[++cnt_edge] = {w, x, y}; }
struct Tree {
  ll w;
  int to, next;
} e_tr[M];
int head[N], cnt_tree;
void add_treeEdge(int x, int y, ll w = 1) {
  e_tr[++cnt_tree] = {w, y, head[x]};
  head[x] = cnt_tree;
}
int fa[N];
int find(int x) { return x == fa[x] ? fa[x] : fa[x] = find(fa[x]); }
void merge(int x, int y) { fa[find(x)] = find(y); }
void kruskal(int n, int k = 1) {
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
}
int f[K][N], dep[N];
ll minw[K][N];
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
ll lca(int x, int y) {
  if (dep[x] < dep[y]) swap(x, y);
  ll ret = LLONG_MAX;
  for (int i = 0, d = dep[x] - dep[y]; d; ++i, d >>= 1)
    if (d & 1) {
      ret = min(ret, minw[i][x]);
      x = f[i][x];
    }
  if (x == y) return ret;
  for (int i = K - 1; i >= 0; --i)
    if (f[i][x] != f[i][y]) {
      ret = min(ret, min(minw[i][x], minw[i][y]));
      x = f[i][x];
      y = f[i][y];
    }
  return min(ret, min(minw[0][x], minw[0][y]));
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  int x, y, z;
  for (int i = 1; i <= (m); ++i) {
    cin >> x >> y >> z;
    addEdge(x, y, z);
    addEdge(y, x, z);
  }
  kruskal(n);
  for (int i = 1; i <= n; ++i)
    if (!vis[i]) {
      dep[i] = 1;
      f[0][i] = i;
      minw[0][i] = LLONG_MAX;
      dfs(i);
    }
  for (int i = 1; i < K; ++i)
    for (int x = 1; x <= n; ++x) {
      f[i][x] = f[i - 1][f[i - 1][x]];
      minw[i][x] = min(minw[i - 1][x], minw[i - 1][f[i - 1][x]]);
    }
  int q;
  cin >> q;
  for (int i = 1; i <= q; ++i) {
    cin >> x >> y;
    if (find(x) != find(y)) {
      cout << "-1\n";
      continue;
    }
    cout << lca(x, y) << '\n';
  }
  return 0;
}
