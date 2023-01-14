#include <bits/stdc++.h>
using namespace std;
const int M = 1e7 + 5, N = 2e6 + 5;
struct Edge {
  int w, to, next;
} e[M];
int head[N], cnt_edge;
void addEdge(int x, int y, int w = 1) {
  e[++cnt_edge] = {w, y, head[x]};
  head[x] = cnt_edge;
}
typedef pair<long long, int> Pli;
long long dis[N];
void dijkstra(int s) {
  priority_queue<Pli, vector<Pli>, greater<Pli>> q;
  memset(dis, 0x3f, sizeof(dis));
  dis[s] = 0;
  q.push(Pli(0, s));
  while (!q.empty()) {
    Pli now = q.top();
    q.pop();
    int v = now.second;
    if (dis[v] < now.first) continue;
    for (int i = head[v], to; i; i = e[i].next) {
      to = e[i].to;
      if (dis[to] > dis[v] + e[i].w) q.push(Pli(dis[to] = dis[v] + e[i].w, to));
    }
  }
}
void init(int n, int m) {
  int _, x, y;
  int s = 0, t = 2 * (n - 1) * (m - 1) + 1;
  for (int i = 0; i < n; ++i)
    for (int j = 1; j < m; ++j) {
      cin >> _;
      y = j * 2 + i * (m - 1) * 2;
      x = y - 2 * m + 1;
      x = x < s ? s : x;
      y = y > t ? t : y;
      addEdge(x, y, _);
      addEdge(y, x, _);
    }
  for (int i = 1; i < n; ++i)
    for (int j = 0; j < m; ++j) {
      cin >> _;
      y = j * 2 + (i - 1) * (m - 1) * 2 + 1;
      x = j == 0 ? t : y - 1;
      y = j == m - 1 ? s : y;
      addEdge(x, y, _);
      addEdge(y, x, _);
    }
  for (int i = 1; i < n; ++i)
    for (int j = 1; j < m; ++j) {
      cin >> _;
      y = j * 2 + (i - 1) * (m - 1) * 2;
      x = y - 1;
      addEdge(x, y, _);
      addEdge(y, x, _);
    }
}
int main() {
  int n, m;
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m;
  init(n, m);
  int s = 0, t = 2 * (n - 1) * (m - 1) + 1;
  dijkstra(s);
  cout << dis[t];
  return 0;
}
