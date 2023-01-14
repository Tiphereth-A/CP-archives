#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define for_(i, l, r, vars...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vars; i <= i##end; ++i)
const int OFFSET = 5;
const int N = 5e5 + OFFSET;
const int M = 1e6 + OFFSET;
struct Edge {
  int w, to, next;
  Edge(int _w = 0, int _to = 0, int _next = 0): w(_w), to(_to), next(_next) {}
} e[M];
int head[N], fa[N], cnt_edge;
void addEdge(int x, int y, int w = 1) {
  e[++cnt_edge] = Edge(w, y, head[x]);
  head[x] = cnt_edge;
}
#define for_graph_(head, e, i, now) \
  for (int i = head[now], to = e[i].to; i; to = e[i = e[i].next].to)
int n;
string s;
i64 sum[N], pre[N];
stack<int> stk;
void dfs(int now) {
  int tmp = 0;
  if (s[now] == ')' && !stk.empty()) {
    pre[now] = pre[fa[tmp = stk.top()]] + 1;
    stk.pop();
  } else if (s[now] == '(') stk.push(now);
  sum[now] = sum[fa[now]] + pre[now];
  for_graph_(head, e, i, now) dfs(to);
  if (tmp) stk.push(tmp);
  else if (!stk.empty()) stk.pop();
}
int main() {
  cin >> n >> s;
  s = " " + s;
  for_(i, 2, n, x) {
    cin >> x;
    addEdge(fa[i] = x, i);
  }
  dfs(1);
  i64 ans = 0;
  for_(i, 1, n) ans ^= sum[i] * i;
  cout << ans;
}
