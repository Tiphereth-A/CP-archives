#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define _for_graph(head, e, i, now) \
  for (int i = head[now], to = e[i].to; i; to = e[i = e[i].next].to)
#define _run_exit(expressions) _run_return(expressions, 0)
#define _run_return(expressions, val) return (expressions), val
#define _run_continue(expressions) \
  {                                \
    expressions;                   \
    continue;                      \
  }
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
const int OFFSET = 5;
const int N = 1e4 + OFFSET, M = 1e5 + OFFSET;
struct Edge {
  int to, next;
  Edge(int _to = 0, int _next = 0): to(_to), next(_next) {}
} e[M];
int head[N], cnt_edge;
int out[N];
void addEdge(int head[], int x, int y) {
  e[++cnt_edge] = Edge(y, head[x]);
  head[x] = cnt_edge;
}
int dfn[N], low[N], cnt_dfn;
stack<int> stk;
bool in_stk[N];
int scc_id[N], scc_size[N], cnt_scc;
void tarjan(int now) {
  in_stk[now] = 1;
  dfn[now] = low[now] = ++cnt_dfn;
  stk.push(now);
  _for_graph(head, e, i, now)
    if (!dfn[to]) {
      tarjan(to);
      chkmin(low[now], low[to]);
    } else if (in_stk[to]) chkmin(low[now], dfn[to]);
  if (dfn[now] == low[now]) {
    ++cnt_scc;
    while (stk.top() != now) {
      ++scc_size[scc_id[stk.top()] = cnt_scc];
      in_stk[stk.top()] = 0;
      stk.pop();
    }
    ++scc_size[scc_id[stk.top()] = cnt_scc];
    in_stk[stk.top()] = 0;
    stk.pop();
  }
}
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  int x, y;
  _for(i, 1, m) {
    scanf("%d%d", &x, &y);
    addEdge(head, x, y);
  }
  _for(i, 1, n)
    if (!dfn[i]) tarjan(i);
  _for(i, 1, m)
    if (cnt_scc == 1) _run_exit(printf("%d", scc_size[1]));
  _for(i, 1, n)
    _for_graph(head, e, j, i) {
      if (scc_id[i] == scc_id[to]) continue;
      ++out[scc_id[i]];
    }
  int ans = 0;
  _for(i, 1, cnt_scc)
    if (!out[i]) {
      if (!ans) _run_continue(ans = i);
      if (ans != i) _run_exit(puts("0"));
    }
  printf("%d", scc_size[ans]);
  return 0;
}
