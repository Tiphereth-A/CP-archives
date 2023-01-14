#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
#define _set_nul(a) memset(a, 0, sizeof(a))
const int OFFSET = 5;
const int N = 2e5 + OFFSET, M = 4e5 + OFFSET, K = 21;
struct Edge {
  i64 w;
  int to, next;
} e[M];
int head[N], cnt_edge;
void addEdge(int x, int y, i64 w = 1) {
  e[++cnt_edge] = {w, y, head[x]};
  head[x] = cnt_edge;
}
i64 dis[N], dis2[N];
void dfs(int now, int fa) {
  for (int i = head[now], to; i; i = e[i].next) {
    to = e[i].to;
    if (to == fa) continue;
    dis[to] = dis[now] + e[i].w;
    dfs(to, now);
  }
}
int main() {
  int n;
  scanf("%d%*d", &n);
  int x, y;
  i64 z;
  _for(i, 1, n - 1) {
    scanf("%d%d%lld", &x, &y, &z);
    addEdge(x, y, z);
    addEdge(y, x, z);
  }
  dfs(1, 0);
  int p = 0;
  i64 max_p = 0;
  _for(i, 1, n)
    if (dis[i] > max_p) max_p = dis[p = i];
  _set_nul(dis);
  dfs(p, 0);
  int q = max_p = 0;
  _for(i, 1, n)
    if (dis[i] > max_p) max_p = dis[q = i];
  memcpy(dis2, dis, sizeof(dis2));
  _set_nul(dis);
  dfs(q, 0);
  i64 ans = max_p;
  _for(i, 1, n)
    if (ans < max_p + min(dis[i], dis2[i])) ans = max_p + min(dis[i], dis2[i]);
  printf("%lld", ans);
  return 0;
}
