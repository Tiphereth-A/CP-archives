#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
struct Edge {
  int w, to, next;
} e[N * 2];
int head[N], cnt_edge;
void addEdge(int x, int y, int w) {
  e[++cnt_edge] = {w, y, head[x]};
  head[x] = cnt_edge;
}
int n;
i64 siz[N], val[N];
i64 dis[N], t[N];
i64 ans[N];
void dfs(int now, int fa) {
  siz[now] = 1;
  t[now] = val[now];
  for (int i = head[now], to; i; i = e[i].next) {
    to = e[i].to;
    if (to == fa) continue;
    dis[to] = dis[now] + e[i].w;
    dfs(to, now);
    siz[now] += siz[to];
    t[now] += t[to];
  }
}
void dfs(int now, int fa, i64 dis_sum, i64 val_dis_sum) {
  ans[now] = val[now] * dis_sum + val_dis_sum;
  for (int i = head[now], to; i; i = e[i].next) {
    to = e[i].to;
    if (to == fa) continue;
    dfs(to,
        now,
        dis_sum + e[i].w * (n - 2 * siz[to]),
        val_dis_sum + e[i].w * (t[1] - 2 * t[to]));
  }
}
int main() {
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> val[i];
  for (int i = 1, u, v, w; i < n; ++i) {
    cin >> u >> v >> w;
    addEdge(u, v, w);
    addEdge(v, u, w);
  }
  dfs(1, 0);
  i64 dis_sum = 0, val_dis_sum = 0;
  for (int i = 1; i <= n; ++i) {
    dis_sum += dis[i];
    val_dis_sum += val[i] * dis[i];
  }
  dfs(1, 0, dis_sum, val_dis_sum);
  for (int i = 1; i <= n; ++i) cout << ans[i] << endl;
  return 0;
}
