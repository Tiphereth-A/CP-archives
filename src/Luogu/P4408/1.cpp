#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 5, M = 4e5 + 5;
struct Edge {
  ll w;
  int to, next;
} e[M];
int head[N], cnt_edge;
void addEdge(int x, int y, ll w = 1) {
  e[++cnt_edge] = {w, y, head[x]};
  head[x] = cnt_edge;
}
ll dis[N], dis2[N];
void dfs(int now, int fa) {
  for (int i = head[now], to; i; i = e[i].next) {
    to = e[i].to;
    if (to == fa) continue;
    dis[to] = dis[now] + e[i].w;
    dfs(to, now);
  }
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  cin >> n;
  int m;
  cin >> m;
  for (int i = 1, x, y; i < n; ++i) {
    ll z;
    cin >> x >> y >> z;
    addEdge(x, y, z);
    addEdge(y, x, z);
  }
  dfs(1, 0);
  int p = 0;
  ll max_p = 0;
  for (int i = 1; i <= n; ++i)
    if (dis[i] > max_p) max_p = dis[p = i];
  memset(dis, 0, sizeof(dis));
  dfs(p, 0);
  int q = max_p = 0;
  for (int i = 1; i <= n; ++i)
    if (dis[i] > max_p) max_p = dis[q = i];
  memcpy(dis2, dis, sizeof(dis2));
  memset(dis, 0, sizeof(dis));
  dfs(q, 0);
  ll ans = max_p;
  for (int i = 1; i <= n; ++i) ans = max(ans, max_p + min(dis[i], dis2[i]));
  cout << ans << '\n';
  return 0;
}
