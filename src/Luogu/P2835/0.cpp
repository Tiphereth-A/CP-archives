#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
#define _for_graph(head, e, i, now) \
  for (int i = head[now], to = e[i].to; i; to = e[i = e[i].next].to)
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
const int OFFSET = 5;
const int N = 400 + OFFSET, M = 1e5 + OFFSET, K = 21;
struct Edge {
  int to, next;
  Edge(int _to = 0, int _next = 0): to(_to), next(_next) {}
} e[M];
int head[N], cnt_edge;
void addEdge(int x, int y) {
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
int in[N], out[N];
int main() {
  int n;
  scanf("%d", &n);
  int x;
  _for(i, 1, n)
    while (scanf("%d", &x), x) addEdge(i, x);
  _for(i, 1, n)
    if (!dfn[i]) tarjan(i);
  _for(i, 1, n)
    _for_graph(head, e, j, i) {
      if (scc_id[to] == scc_id[i]) continue;
      ++in[scc_id[to]];
      ++out[scc_id[i]];
    }
  int cnt_in = 0, cnt_out = 0;
  _for(i, 1, cnt_scc) {
    cnt_in += !in[i];
    cnt_out += !out[i];
  }
  printf("%d\n", cnt_in);
FINISHED:
  return 0;
}
