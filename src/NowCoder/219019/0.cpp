#include <bits/stdc++.h>
using namespace std;
const int M = 2e4 + 5, N = 1e3 + 5;
struct Edge {
  int w, to, next;
} e[M];
int deg[N];
int head[N], cnt_edge;
void addEdge(int x, int y, int w = 1) {
  e[++cnt_edge] = {w, y, head[x]};
  head[x] = cnt_edge;
}
bool vis[N];
int _v;
int dfs(int now) {
  int ret = deg[now];
  for (int i = head[now]; i; i = e[i].next)
    if (!vis[e[i].to]) {
      vis[e[i].to] = 1;
      ++_v;
      ret += dfs(e[i].to);
    }
  return ret;
}
int main() {
  int n;
  scanf("%d", &n);
  int con, fix;
  for (int i = 1, vertex, edges; i <= n; ++i) {
    cin >> vertex >> edges;
    memset(head, cnt_edge = con = fix = 0, sizeof(head));
    memset(deg, 0, sizeof(deg));
    memset(vis, 1, sizeof(vis));
    for (int i = 1, a, b; i <= edges; ++i) {
      cin >> a >> b;
      addEdge(a, b);
      addEdge(b, a);
      ++deg[a];
      ++deg[b];
      vis[a] = vis[b] = 0;
    }
    for (int now = 1; now <= vertex; ++now)
      if (!vis[now]) {
        ++con;
        vis[now] = _v = 1;
        int _e = dfs(now);
        if (_e / 2 >= _v) ++fix;
      }
    cout << "Night sky #" << i << ": " << con << " constellations, of which "
         << fix << " need to be fixed." << endl;
    if (i != n) cout << endl;
  }
  return 0;
}
