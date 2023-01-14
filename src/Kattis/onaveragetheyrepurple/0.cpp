#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5, M = 2e5 + 5;
struct Edge {
  int w, to, next;
} e[M];
int head[N], cnt_edge;
void addEdge(int x, int y, int w = 1) {
  e[++cnt_edge] = {w, y, head[x]};
  head[x] = cnt_edge;
}
typedef pair<int, int> P_i_i;
int dis[N];
void dijkstra(int s) {
  priority_queue<P_i_i, vector<P_i_i>, greater<P_i_i>> q;
  memset(dis, 0x3f, sizeof(dis));
  dis[s] = 0;
  q.push(P_i_i(0, s));
  while (!q.empty()) {
    P_i_i now = q.top();
    q.pop();
    int v = now.second;
    if (dis[v] < now.first) continue;
    for (int i = head[v], to; i; i = e[i].next) {
      to = e[i].to;
      if (dis[to] > dis[v] + e[i].w)
        q.push(P_i_i(dis[to] = dis[v] + e[i].w, to));
    }
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n, m;
  cin >> n >> m;
  for (int i = 1, s, t; i <= m; ++i) {
    cin >> s >> t;
    addEdge(s, t);
    addEdge(t, s);
  }
  dijkstra(1);
  cout << dis[n] - 1;
  return 0;
}
