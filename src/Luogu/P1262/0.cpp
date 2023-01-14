#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
#define _for_graph(head, e, i, now) \
  for (int i = head[now], to = e[i].to; i; to = e[i = e[i].next].to)
#define _set_inf_n(a, n) memset(a, 0x3f, sizeof(a[0]) * (n))
#define _run_exit(expressions) _run_return(expressions, 0)
#define _run_return(expressions, val) return (expressions), val
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
const int OFFSET = 5;
const int N = 1e4 + OFFSET, M = 1e5 + OFFSET;
const int INF = 0x3f3f3f3f;
int a[N];
struct Edge {
  int to, next;
  Edge(int _to = 0, int _next = 0): to(_to), next(_next) {}
} e[M];
int head[N], cnt_edge;
int in[N], out[N];
void addEdge(int x, int y) {
  e[++cnt_edge] = Edge(y, head[x]);
  head[x] = cnt_edge;
  ++in[y];
  ++out[x];
}
int dfn[N], low[N], cnt_dfn;
stack<int> stk;
bool in_stk[N];
int scc_id[N], scc_size[N], cnt_scc;
int val[N], scc_in[N];
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
    val[++cnt_scc] = INF;
    while (stk.top() != now) {
      chkmin(val[cnt_scc], a[stk.top()]);
      ++scc_size[scc_id[stk.top()] = cnt_scc];
      in_stk[stk.top()] = 0;
      stk.pop();
    }
    chkmin(val[cnt_scc], a[stk.top()]);
    ++scc_size[scc_id[stk.top()] = cnt_scc];
    in_stk[stk.top()] = 0;
    stk.pop();
  }
}
int fa[N];
int find(int x) { return x == fa[x] ? fa[x] : fa[x] = find(fa[x]); }
void merge(int x, int y) { fa[find(x)] = find(y); }
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n, p, r;
  cin >> n >> p;
  _set_inf_n(a, n + 1);
  int x, y;
  _for(i, 1, p) {
    cin >> x >> y;
    a[x] = y;
  }
  cin >> r;
  _for(i, 1, r) {
    cin >> x >> y;
    addEdge(x, y);
  }
  _for(i, 1, n)
    if (!dfn[i] && a[i] != INF) tarjan(i);
  _for(i, 1, n)
    if (!dfn[i]) _run_exit(cout << "NO\n" << i);
  _for(i, 1, cnt_scc) fa[i] = i;
  _for(i, 1, n)
    _for_graph(head, e, j, i)
      if (find(scc_id[i]) != find(scc_id[to])) {
        ++scc_in[scc_id[to]];
        merge(scc_id[i], scc_id[to]);
      }
  i64 ans = 0;
  _for(i, 1, cnt_scc)
    if (!scc_in[i]) ans += val[i];
  cout << "YES\n" << ans;
  return 0;
}
