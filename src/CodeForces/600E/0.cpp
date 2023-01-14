#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5, M = 2e5 + 5;
struct Edge {
  int to, next;
} e[M];
int head[N], cnt_edge;
void addEdge(int x, int y) {
  e[++cnt_edge] = {y, head[x]};
  head[x] = cnt_edge;
}
i64 siz[N], son[N];
void init(int p = 1, int fa = 0) {
  siz[p] = 1;
  for (int i = head[p], to; i; i = e[i].next) {
    to = e[i].to;
    if (to == fa) continue;
    init(to, p);
    siz[p] += siz[to];
    if (siz[to] > siz[son[p]]) son[p] = to;
  }
}
i64 ans[N], cnt[N];
int color[N];
int heavy_son;
i64 sum, max_cnt;
void count(int p, int fa, bool erase = false) {
  cnt[color[p]] += erase ? -1 : 1;
  if (max_cnt < cnt[color[p]]) {
    max_cnt = cnt[color[p]];
    sum = color[p];
  } else if (max_cnt == cnt[color[p]]) sum += color[p];
  for (int i = head[p], to; i; i = e[i].next) {
    to = e[i].to;
    if (to == fa || to == heavy_son) continue;
    count(to, p, erase);
  }
}
void dfs(int p = 1, int fa = 0, bool erase = true) {
  for (int i = head[p], to; i; i = e[i].next) {
    to = e[i].to;
    if (to == fa || to == son[p]) continue;
    dfs(to, p);
  }
  if (son[p]) {
    dfs(son[p], p, false);
    heavy_son = son[p];
  }
  count(p, fa);
  heavy_son = 0;
  ans[p] = sum;
  if (erase) {
    count(p, fa, true);
    sum = max_cnt = 0;
  }
  return;
}
int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> color[i];
  for (int i = 1, x, y; i < n; ++i) {
    cin >> x >> y;
    addEdge(x, y);
    addEdge(y, x);
  }
  init();
  dfs();
  for (int i = 1; i <= n; ++i) cout << ans[i] << " ";
  return 0;
}
