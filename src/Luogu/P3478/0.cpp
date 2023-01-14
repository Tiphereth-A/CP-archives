#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _run_return_void(expressions) \
  {                                   \
    expressions;                      \
    return;                           \
  }
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
const uint32_t OFFSET = 5;
const uint32_t N = 1e6 + OFFSET, M = 2e6 + OFFSET;
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
i64 sz[N], dep[N];
void dfs(int now, int fa) {
  sz[now] = 1;
  dep[now] = dep[fa] + 1;
  _for_graph(head, e, i, now) {
    if (to == fa) continue;
    dfs(to, now);
    sz[now] += sz[to];
  }
}
int n;
void dfs2(int now, int fa) {
  _for_graph(head, e, i, now) {
    if (to == fa) continue;
    ans[to] = ans[now] + n - 2 * sz[to];
    dfs2(to, now);
  }
}
auto solve() -> void {
  cin >> n;
  if (n == 0) _run_return_void(cout << '0');
  _for(i, 1, n - 1, x, y) {
    cin >> x >> y;
    addEdge(x, y);
    addEdge(y, x);
  }
  dfs(1, 0);
  _for(i, 1, n) ans[1] += dep[i];
  dfs2(1, 0);
  i64 max_ans = ans[1], idx = 1;
  _for(i, 2, n)
    if (ans[i] > max_ans) max_ans = ans[idx = i];
  cout << idx;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
