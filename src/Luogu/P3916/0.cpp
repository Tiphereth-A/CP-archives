#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
#define _rfor(i, r, l) for (decltype(l + r) i = (r); i >= (l); --i)
#define _for_graph(head, e, i, now) \
  for (int i = head[now], to = e[i].to; i; to = e[i = e[i].next].to)
const int OFFSET = 5;
const int N = 1e5 + OFFSET, M = 2e5 + OFFSET, K = 21;
struct Edge {
  int to, next;
  Edge(int _to = 0, int _next = 0): to(_to), next(_next) {}
} e[M];
int head[N], cnt_edge;
void addEdge(int x, int y) {
  e[++cnt_edge] = Edge(y, head[x]);
  head[x] = cnt_edge;
}
int ans[N];
void dfs(int now, int ast) {
  ans[now] = ast;
  _for_graph(head, e, i, now)
    if (!ans[to]) dfs(to, ast);
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n, m;
  cin >> n >> m;
  _for(i, 1, m) {
    int x, y;
    cin >> x >> y;
    addEdge(y, x);
  }
  _rfor(i, n, 1) {
    if (ans[i]) continue;
    dfs(i, i);
  }
  _for(i, 1, n) cout << ans[i] << " \n"[i == n];
  return 0;
}
