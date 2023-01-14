#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5, M = 2e5 + 5;
struct Edge {
  bool w;
  int to, next;
} e[M];
int head[N], cnt_edge;
void addEdge(int x, int y, bool w = 1) {
  e[++cnt_edge] = {w, y, head[x]};
  head[x] = cnt_edge;
}
bool color[N];
void dfs(int now, int fa) {
  for (int i = head[now], to; i; i = e[i].next) {
    if ((to = e[i].to) == fa) continue;
    color[to] = e[i].w ^ color[now];
    dfs(to, now);
  }
}
int main() {
  int n;
  cin >> n;
  for (int i = 1, u, v, w; i < n; ++i) {
    cin >> u >> v >> w;
    addEdge(u, v, w & 1);
    addEdge(v, u, w & 1);
  }
  dfs(1, 0);
  for (int i = 1; i <= n; ++i) cout << color[i] << endl;
  return 0;
}
