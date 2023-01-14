#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5, M = 4e5 + 5;
struct Edge {
  int to, next;
} e[M];
int head[N], cnt_e;
void addEdge(int u, int v) {
  e[++cnt_e] = {v, head[u]};
  head[u] = cnt_e;
}
#define _for_graph(i, now) \
  for (int i = head[now], v = e[i].to; i; v = e[i = e[i].next].to)
int fa[N];
int64_t sz[N];
int find(int x) {
  if (x == fa[x]) return x;
  int rt = find(fa[x]);
  return fa[x] = rt;
}
void merge(int u, int v) {
  int fu = find(u), fv = find(v);
  if (fu == fv) return;
  fa[fu] = fv;
  sz[fv] += sz[fu];
}
struct Node {
  int u, v, w;
} q[N];
bool vis[N];
int64_t sum[2];
int endp;
bool res;
void dfs(int now, int fa, int idx) {
  if (vis[now]) {
    if (now != endp) return;
    res = !idx;
    return;
  }
  vis[now] = 1;
  sum[idx] += sz[now];
  _for_graph(i, now) {
    if (v == fa) continue;
    dfs(v, now, idx ^ 1);
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= m; ++i) cin >> q[i].u >> q[i].v >> q[i].w;
  int maxw = 0;
  for (int i = 1; i <= m; ++i) maxw = max(maxw, q[i].w);
  int64_t ans = 0;
  for (int dig = 30; dig >= 0; --dig) {
    int64_t now = 1ll << dig;
    if (now > maxw) continue;
    memset(head, 0, sizeof(head[0]) * (n + 1));
    memset(vis, 0, sizeof(vis[0]) * (n + 1));
    cnt_e = 0;
    for (int i = 1; i <= n; ++i) sz[fa[i] = i] = 1;
    for (int i = 1; i <= m; ++i)
      if (!(q[i].w & now)) merge(q[i].u, q[i].v);
    for (int i = 1; i <= m; ++i)
      if (q[i].w & now) {
        addEdge(find(q[i].u), find(q[i].v));
        addEdge(find(q[i].v), find(q[i].u));
      }
    for (int i = 1; i <= n; ++i)
      if (!vis[i]) {
        res = 1;
        dfs(endp = i, sum[0] = sum[1] = 0, 0);
        if (!res) {
          cout << "-1";
          return 0;
        }
        ans += min(sum[0], sum[1]) * now;
      }
  }
  cout << ans;
}
