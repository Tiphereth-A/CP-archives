#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
const uint32_t OFFSET = 5;
const uint32_t N = 1e5 + OFFSET, M = 2e5 + OFFSET, K = 19;
const int INF = 0x3f3f3f3f;
struct Edge {
  int w, to, next;
  Edge(int _w = 0, int _to = 0, int _next = 0): w(_w), to(_to), next(_next) {}
} e[M];
int head[N], cnt_edge;
int in[N], out[N];
void addEdge(int x, int y, int w = 1) {
  e[++cnt_edge] = Edge(w, y, head[x]);
  head[x] = cnt_edge;
  ++in[y];
  ++out[x];
}
int dist[K][N];
void dijkstra(int *dis, int s) {
  priority_queue<pair<int, int>,
                 vector<pair<int, int>>,
                 greater<pair<int, int>>>
    q;
  q.emplace(dis[s] = 0, s);
  while (!q.empty()) {
    auto [dis_now, now] = q.top();
    q.pop();
    if (dis[now] < dis_now) continue;
    for (int i = head[now], to; i; i = e[i].next)
      if (dis[to = e[i].to] > dis[now] + e[i].w)
        q.emplace(dis[to] = dis[now] + e[i].w, to);
  }
}
pair<int, double> bicycles[K];
double expectation[1 << K][K];
int t, r, n, m, k;
double dp(int state, int now) {
  if (expectation[state][now] >= 0) return expectation[state][now];
  double ret = bicycles[now].second * dist[now][n] / t +
               (1 - bicycles[now].second) * dist[now][n] / r;
  _for(i, 0, k - 1) {
    if (i == now) continue;
    if (state & (1 << i)) continue;
    ret = min(ret,
              bicycles[now].second * (dp(state | (1 << i), i) +
                                      1.0 * dist[now][bicycles[i].first] / t) +
                (1 - bicycles[now].second) * dist[now][n] / r);
  }
  return expectation[state][now] = ret;
}
auto solve() -> void {
  cin >> t >> r >> n >> m;
  _for(i, 1, m, u, v, w) {
    cin >> u >> v >> w;
    addEdge(u, v, w);
    addEdge(v, u, w);
  }
  cin >> k;
  _for(i, 0, k - 1, a, p) {
    cin >> a >> p;
    bicycles[i] = {a, p / 100.0};
  }
  bicycles[k] = {1, 1};
  memset(dist, 0x3f, sizeof(dist));
  _for(i, 0, k) dijkstra(dist[i], bicycles[i].first);
  if (dist[k][n] == INF) {
    cout << "-1\n";
    return;
  }
  _for(i, 0, (1 << (k + 1)) - 1)
    _for(j, 0, k) expectation[i][j] = -114514;
  cout << fixed << setprecision(6) << dp(1 << k, k);
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
