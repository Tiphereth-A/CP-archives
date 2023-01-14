#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int N = 1e5 + 5, M = 4e5 + 5;
struct Edge {
  int64_t w;
  int to, next;
  Edge(int64_t _w = 0, int _to = 0, int _next = 0)
    : w(_w), to(_to), next(_next) {}
} e[M];
int head[N], cnt_edge;
void addEdge(int x, int y, int64_t w = 1) {
  e[++cnt_edge] = Edge(w, y, head[x]);
  head[x] = cnt_edge;
}
#define _for_graph(head, e, i, now) \
  for (int i = head[now], to = e[i].to; i; to = e[i = e[i].next].to)
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
i64 w;
int low[N], dfn[N], cnt_dfs;
int cnt[N];
void tarjan(int u, int fa = 0) {
  low[u] = dfn[u] = ++cnt_dfs;
  cnt[u] = 0;
  _for_graph(head, e, i, u) {
    ++cnt[to];
    if (to == fa) continue;
    if (!dfn[to]) {
      tarjan(to, u);
      low[u] = min(low[u], low[to]);
      cnt[u] += cnt[to];
    } else low[u] = min(low[u], dfn[to]);
    if (low[to] > dfn[u]) {
      if (cnt[to] % 2 == 0) w = min(w, e[i].w);
    } else w = min(w, e[i].w);
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, m;
  cin >> n >> m;
  int u, v;
  i64 sum = 0;
  if (m % 2 == 0) {
    _for(i, 1, m) {
      cin >> u >> v >> w;
      sum += w;
    }
    cout << sum;
    return 0;
  }
  _for(i, 1, m) {
    cin >> u >> v >> w;
    addEdge(u, v, w);
    addEdge(v, u, w);
    sum += w;
  }
  w = INT64_MAX;
  tarjan(1);
  cout << sum - w;
  return 0;
}
