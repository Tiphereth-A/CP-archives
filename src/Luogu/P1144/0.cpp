#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
const uint32_t OFFSET = 5;
const uint32_t N = 1e6 + OFFSET, M = 4e6 + OFFSET;
const uint32_t MOD = 1e5 + 3;
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
int dis[N], cnt[N];
void dijkstra(int s) {
  priority_queue<pii, vector<pii>, greater<pii>> q;
  memset(dis, 0x3f, sizeof(dis));
  dis[s] = 0;
  cnt[s] = 1;
  q.emplace(0, s);
  while (!q.empty()) {
    pii now = q.top();
    q.pop();
    int v = now.second;
    if (dis[v] < now.first) continue;
    for (int i = head[v], to; i; i = e[i].next) {
      to = e[i].to;
      if (dis[to] > dis[v] + e[i].w) {
        cnt[to] = cnt[v];
        q.emplace(dis[to] = dis[v] + e[i].w, to);
      } else if (dis[to] == dis[v] + e[i].w) (cnt[to] += cnt[v]) %= MOD;
    }
  }
}
auto solve() -> void {
  int n, m;
  cin >> n >> m;
  _for(i, 1, m, x, y) {
    cin >> x >> y;
    addEdge(x, y);
    addEdge(y, x);
  }
  dijkstra(1);
  _for(i, 1, n) cout << cnt[i] << '\n';
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
