#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (int i = (l), i##end = (r), ##vals; i <= i##end; ++i)
const uint32_t OFFSET = 5;
const uint32_t N = 1e6 + OFFSET, M = 2e6 + OFFSET;
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
i64 a[N];
i64 ans[N];
i64 sz[N], dep[N];
i64 sum_sz;
void dfs(int now, int fa) {
  sz[now] = a[now];
  _for_graph(head, e, i, now) {
    if (to == fa) continue;
    dfs(to, now);
    dep[to] = dep[now] + e[i].w * sz[to];
    sz[now] += sz[to];
  }
}
void dfs2(int now, int fa) {
  _for_graph(head, e, i, now) {
    if (to == fa) continue;
    ans[to] = ans[now] + (sum_sz - 2 * sz[to]) * e[i].w;
    dfs2(to, now);
  }
}
auto solve() -> void {
  int n;
  cin >> n;
  _for(i, 1, n) cin >> a[i];
  _for(i, 1, n) sum_sz += a[i];
  _for(i, 1, n - 1, x, y, w) {
    cin >> x >> y >> w;
    addEdge(x, y, w);
    addEdge(y, x, w);
  }
  dfs(1, 0);
  _for(i, 1, n) ans[1] += dep[i];
  dfs2(1, 0);
  i64 max_ans = ans[1];
  _for(i, 2, n)
    if (ans[i] < max_ans) max_ans = ans[i];
  cout << max_ans;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
