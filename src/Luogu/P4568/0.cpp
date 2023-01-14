#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
const uint32_t OFFSET = 5;
const uint32_t N = 2e5 + OFFSET, M = 4e6 + OFFSET;
struct Edge {
  int w, to, next;
  Edge(int _w = 0, int _to = 0, int _next = -1): w(_w), to(_to), next(_next) {}
} e[M];
int head[N], cnt_edge;
void addEdge(int x, int y, int w = 1) {
  e[++cnt_edge] = Edge(w, y, head[x]);
  head[x] = cnt_edge;
}
int dis[N];
void dijkstra(int s) {
  priority_queue<pair<int, int>,
                 vector<pair<int, int>>,
                 greater<pair<int, int>>>
    q;
  memset(dis, 0x3f, sizeof(dis));
  q.emplace(dis[s] = 0, s);
  while (!q.empty()) {
    auto [dis_now, now] = q.top();
    q.pop();
    if (dis[now] < dis_now) continue;
    for (int i = head[now], to; ~i; i = e[i].next)
      if (dis[to = e[i].to] > dis[now] + e[i].w)
        q.emplace(dis[to] = dis[now] + e[i].w, to);
  }
}
auto solve() -> void {
  int n, m, k;
  cin >> n >> m >> k;
  int s, t;
  cin >> s >> t;
  memset(head, 0xff, sizeof(head));
  _for(i, 1, m, a, b, c) {
    cin >> a >> b >> c;
    _for(j, 0, k) {
      addEdge(a + j * n, b + j * n, c);
      addEdge(b + j * n, a + j * n, c);
    }
    _for(j, 0, k - 1) {
      addEdge(a + j * n, b + (j + 1) * n, 0);
      addEdge(b + j * n, a + (j + 1) * n, 0);
    }
  }
  _for(j, 0, k - 1) addEdge(t + j * n, t + (j + 1) * n, 0);
  dijkstra(s);
  cout << dis[t + k * n];
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
