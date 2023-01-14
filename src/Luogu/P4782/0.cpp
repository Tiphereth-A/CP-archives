#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
const uint32_t OFFSET = 5;
const uint32_t N = 2e6 + OFFSET, M = 2e6 + OFFSET;
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
int dfn[N], low[N], cnt_dfn;
stack<int> stk;
bool in_stk[N];
int scc_id[N], cnt_scc;
void tarjan(int now) {
  dfn[now] = low[now] = ++cnt_dfn;
  stk.push(now);
  in_stk[now] = 1;
  _for_graph(head, e, i, now)
    if (!dfn[to]) {
      tarjan(to);
      chkmin(low[now], low[to]);
    } else if (in_stk[to]) chkmin(low[now], dfn[to]);
  if (dfn[now] == low[now]) {
    ++cnt_scc;
    while (stk.top() != now) {
      scc_id[stk.top()] = cnt_scc;
      in_stk[stk.top()] = 0;
      stk.pop();
    }
    scc_id[stk.top()] = cnt_scc;
    in_stk[stk.top()] = 0;
    stk.pop();
  }
}
auto solve() -> void {
  int n, m;
  cin >> n >> m;
  _for(i, 1, m, x, y, a, b) {
    cin >> x >> a >> y >> b;
    addEdge(x + a * n, y + (b ^ 1) * n);
    addEdge(y + b * n, x + (a ^ 1) * n);
  }
  _for(i, 1, n * 2)
    if (!dfn[i]) tarjan(i);
  _for(i, 1, n)
    if (scc_id[i] == scc_id[i + n]) {
      cout << "IMPOSSIBLE\n";
      return;
    }
  cout << "POSSIBLE\n";
  _for(i, 1, n) cout << (scc_id[i] < scc_id[i + n]) << " \n"[i == n];
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
