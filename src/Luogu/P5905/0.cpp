#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
namespace Johnson_shortest_path {
const int N = 3e3 + 5, M = 9e3 + 5;
const int64_t INF = 0x3f3f3f3f3f3f3f3f;
struct Edge {
  int to, next;
  int64_t w;
  Edge(int64_t _w = 0, int _to = 0, int _next = -1)
    : to(_to), next(_next), w(_w) {}
} e[M];
int head[N], cnt_edge;
void addEdge(int x, int y, int w = 1) {
  e[++cnt_edge] = Edge(w, y, head[x]);
  head[x] = cnt_edge;
}
#define _for_graph(head, e, i, now) \
  for (int i = head[now], to = e[i].to; ~i; to = e[i = e[i].next].to)
int n, m;
int vis[N];
int64_t h[N], dis[N];
bool f[N];
bool bellman_ford(int s) {
  queue<int> q;
  memset(h, 0x3f, sizeof(h[0]) * (n + 1));
  h[s] = 0;
  f[s] = true;
  q.push(s);
  while (!q.empty()) {
    int now = q.front();
    q.pop();
    f[now] = 0;
    _for_graph(head, e, i, now)
      if (h[to] > h[now] + e[i].w) {
        h[to] = h[now] + e[i].w;
        if (f[to]) continue;
        if (++vis[to] > n) return false;
        f[to] = true;
        q.push(to);
      }
  }
  return true;
}
void dijkstra(int s) {
  priority_queue<pair<int, int>,
                 vector<pair<int, int>>,
                 greater<pair<int, int>>>
    q;
  memset(dis, 0x3f, sizeof(dis[0]) * (n + 1));
  memset(f, 0, sizeof(f[0]) * (n + 1));
  q.emplace(0, s);
  dis[s] = 0;
  while (!q.empty()) {
    int now = q.top().second;
    q.pop();
    if (f[now]) continue;
    f[now] = 1;
    _for_graph(head, e, i, now)
      if (dis[to] > dis[now] + e[i].w) {
        dis[to] = dis[now] + e[i].w;
        if (!f[to]) q.emplace(dis[to], to);
      }
  }
}
int64_t ans[N][N];
bool init(int vertex_num, int edge_num, const tuple<int, int, int> *edges) {
  n = vertex_num;
  m = edge_num;
  memset(head, 0xff, sizeof(head[0]) * (n + 1));
  _for(i, 1, m) addEdge(get<0>(edges[i]), get<1>(edges[i]), get<2>(edges[i]));
  _for(i, 1, n) addEdge(0, i, 0);
  if (!bellman_ford(0)) return false;
  _for(u, 1, n)
    _for_graph(head, e, i, u) e[i].w += h[u] - h[to];
  _for(i, 1, n) {
    dijkstra(i);
    _for(j, 1, n) ans[i][j] = ((dis[j] == INF) ? INF : (dis[j] + h[j] - h[i]));
  }
  return true;
}
bool is_disconnected(int x, int y) { return ans[x][y] == INF; }
int64_t distance(int x, int y) { return ans[x][y]; }
}  // namespace Johnson_shortest_path
const int INF = 1e9;
tuple<int, int, int> edges[Johnson_shortest_path::M];
auto solve() -> void {
  int n, m;
  cin >> n >> m;
  _for(i, 1, m, u, v, w) {
    cin >> u >> v >> w;
    edges[i] = {u, v, w};
  }
  if (!Johnson_shortest_path::init(n, m, edges)) {
    cout << "-1\n";
    return;
  }
  _for(i, 1, n) {
    i64 ans = 0;
    _for(j, 1, n)
      ans += j * (Johnson_shortest_path::is_disconnected(i, j) ?
                    (i64)(1e9) :
                    Johnson_shortest_path::distance(i, j));
    cout << ans << '\n';
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
