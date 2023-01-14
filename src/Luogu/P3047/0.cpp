#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (int i = (l), i##end = (r), ##vals; i <= i##end; ++i)
const uint32_t OFFSET = 5;
const uint32_t N = 1e5 + OFFSET, M = 2e5 + OFFSET, K = 21;
struct Edge {
  int to, next;
  Edge(int _to = 0, int _next = 0): to(_to), next(_next) {}
} e[M];
int head[N], cnt_edge;
void addEdge(int x, int y) {
  e[++cnt_edge] = Edge(y, head[x]);
  head[x] = cnt_edge;
}
#define _for_graph(head, e, i, now) \
  for (int i = head[now], to = e[i].to; i; to = e[i = e[i].next].to)
i64 ans[N];
i64 val[N][K];
int k;
void dfs(int now, int fa) {
  _for_graph(head, e, i, now) {
    if (to == fa) continue;
    dfs(to, now);
    _for(i, 1, k) val[now][i] += val[to][i - 1];
  }
}
void dfs2(int now, int fa) {
  _for(i, 0, k) ans[now] += val[now][i];
  _for_graph(head, e, i, now) {
    if (to == fa) continue;
    _for(i, 1, k) val[now][i] -= val[to][i - 1];
    _for(i, 1, k) val[to][i] += val[now][i - 1];
    dfs2(to, now);
    _for(i, 1, k) val[to][i] -= val[now][i - 1];
    _for(i, 1, k) val[now][i] += val[to][i - 1];
  }
}
auto solve() -> void {
  int n;
  cin >> n >> k;
  _for(i, 1, n - 1, x, y) {
    cin >> x >> y;
    addEdge(x, y);
    addEdge(y, x);
  }
  _for(i, 1, n) cin >> val[i][0];
  dfs(1, 0);
  dfs2(1, 0);
  _for(i, 1, n) cout << ans[i] << '\n';
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
