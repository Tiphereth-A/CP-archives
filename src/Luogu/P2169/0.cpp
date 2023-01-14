#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
const int N = 2e5 + 5, M = 1e6 + 5;
struct Edge {
  int w, to, next;
  Edge(int _w = 0, int _to = 0, int _next = 0): w(_w), to(_to), next(_next) {}
} e[M];
int head[N], cnt_edge;
void addEdge(int x, int y, int w = 1) {
  e[++cnt_edge] = Edge(w, y, head[x]);
  head[x] = cnt_edge;
}
#define _for_graph(head, e, i, now) \
  for (int i = head[now], to = e[i].to; i; to = e[i = e[i].next].to)
int dfn[N], low[N], cnt_dfn;
stack<int> stk;
bool in_stk[N];
int scc_id[N], cnt_scc;
void tarjan(int now) {
  in_stk[now] = 1;
  dfn[now] = low[now] = ++cnt_dfn;
  stk.push(now);
  _for_graph(head, e, i, now)
    if (!dfn[to]) {
      tarjan(to);
      chkmin(low[now], low[to]);
    } else if (in_stk[to]) chkmin(low[now], dfn[to]);
  if (dfn[now] == low[now]) {
    ++cnt_scc;
    while (stk.top() != now) {
      scc_id[stk.top()] = cnt_scc;
      in_stk[stk.top()] = 0;
      stk.pop();
    }
    scc_id[stk.top()] = cnt_scc;
    in_stk[stk.top()] = 0;
    stk.pop();
  }
}
int u[M], v[M], w[M];
int dis[N];
bool vis_dijk[N];
void dijkstra(int s) {
  priority_queue<pii, vector<pii>, greater<pii>> q;
  memset(dis, 0x3f, sizeof(dis));
  dis[s] = 0;
  q.emplace(0, s);
  while (!q.empty()) {
    pii now = q.top();
    q.pop();
    int v = now.second;
    if (dis[v] < now.first) continue;
    _for_graph(head, e, i, v) {
      to = e[i].to;
      if (dis[to] > dis[v] + e[i].w) q.emplace(dis[to] = dis[v] + e[i].w, to);
    }
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, m;
  cin >> n >> m;
  _for(i, 1, m) {
    cin >> u[i] >> v[i] >> w[i];
    addEdge(u[i], v[i], w[i]);
  }
  _for(i, 1, n)
    if (!dfn[i]) tarjan(i);
  cnt_edge = 0;
  memset(head, 0, sizeof(head[0]) * (n + 1));
  _for(i, 1, m)
    if (scc_id[u[i]] != scc_id[v[i]]) addEdge(scc_id[u[i]], scc_id[v[i]], w[i]);
  dijkstra(scc_id[1]);
  cout << dis[scc_id[n]];
  return 0;
}
