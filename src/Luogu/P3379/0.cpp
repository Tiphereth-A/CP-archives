#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
const uint32_t OFFSET = 5;
const uint32_t N = 5e5 + OFFSET, M = 1e6 + OFFSET;
struct Edge {
  int to, next;
  Edge(int _to = 0, int _next = 0): to(_to), next(_next) {}
} e[N * 2];
int head[N], cnt_edge;
void addEdge(int x, int y) {
  e[++cnt_edge] = Edge(y, head[x]);
  head[x] = cnt_edge;
}
struct QEdge {
  int from, to, next, lca;
  QEdge(int _from = 0, int _to = 0, int _next = 0)
    : from(_from), to(_to), next(_next), lca(-1) {}
} qe[M];
int qhead[N], cnt_qedge;
void addQEdge(int x, int y) {
  qe[++cnt_qedge] = QEdge(x, y, qhead[x]);
  qhead[x] = cnt_qedge;
}
#define _for_graph(head, e, i, now) \
  for (int i = head[now], to = e[i].to; i; to = e[i = e[i].next].to)
int fa[N];
int find(int x) { return x == fa[x] ? fa[x] : fa[x] = find(fa[x]); }
bool vis[N];
void tarjan(int now) {
  vis[now] = 1;
  _for_graph(head, e, i, now)
    if (!vis[to]) {
      tarjan(to);
      fa[to] = now;
    }
  _for_graph(qhead, qe, i, now)
    if (vis[to]) qe[i].lca = qe[((i - 1) ^ 1) + 1].lca = find(to);
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, m, r;
  cin >> n >> m >> r;
  _for(i, 1, n) fa[i] = i;
  _for(i, 1, n - 1, u, v) {
    cin >> u >> v;
    addEdge(u, v);
    addEdge(v, u);
  }
  _for(i, 1, m, u, v) {
    cin >> u >> v;
    addQEdge(u, v);
    addQEdge(v, u);
  }
  tarjan(r);
  _for(i, 1, m) {
    QEdge &q = qe[i * 2];
    cout << q.lca << '\n';
  }
  return 0;
}
