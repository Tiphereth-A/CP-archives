#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
#define _set_nul(a) memset(a, 0, sizeof(a))
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
const int OFFSET = 5;
const int N = 5e5 + OFFSET, M = 2e5 + OFFSET, K = 21;
struct Edge {
  int w, to, next;
} e[M];
int head[N], cnt_edge;
void addEdge(int x, int y, int w = 1) {
  e[++cnt_edge] = {w, y, head[x]};
  head[x] = cnt_edge;
}
int dis[N];
void dfs(int now, int fa) {
  for (int i = head[now], to; i; i = e[i].next) {
    to = e[i].to;
    if (to == fa) continue;
    dis[to] = dis[now] + 1;
    dfs(to, now);
  }
}
int main() {
  int n;
  scanf("%d", &n);
  int x, y;
  _for(i, 1, n - 1) {
    scanf("%d%d", &x, &y);
    addEdge(x, y);
    addEdge(y, x);
  }
  dfs(1, 0);
  int p = 0, max_p = 0;
  _for(i, 1, n)
    if (dis[i] > max_p) max_p = dis[p = i];
  _set_nul(dis);
  dfs(p, 0);
  max_p = 0;
  _for(i, 1, n) chkmax(max_p, dis[i]);
  printf("%d", max_p);
  return 0;
}
