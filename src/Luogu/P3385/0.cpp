#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
#define _set_nul_n(a, n) memset(a, 0, sizeof(a[0]) * (n))
#define _set_inf_n(a, n) memset(a, 0x3f, sizeof(a[0]) * (n))
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
const int OFFSET = 5;
const int N = 2e3 + OFFSET, M = 2e5 + OFFSET, K = 21;
struct Edge {
  i64 w;
  int to, next;
  Edge(i64 _w = 0, int _to = 0, int _next = 0): w(_w), to(_to), next(_next) {}
} e[M];
int head[N], cnt_edge;
void addEdge(int x, int y, i64 w = 1) {
  e[++cnt_edge] = Edge(w, y, head[x]);
  head[x] = cnt_edge;
}
i64 d[N], cnt[N];
bool vis[N];
bool spfa(int n, int start = 1) {
  _set_inf_n(d, n + 1);
  _set_nul_n(cnt, n + 1);
  _set_nul_n(vis, n + 1);
  queue<int> q;
  q.push(start);
  vis[start] = 1;
  d[start] = 0;
  while (!q.empty()) {
    int now = q.front();
    q.pop();
    vis[now] = 0;
    for (int i = head[now], to; i; i = e[i].next) {
      to = e[i].to;
      if (e[i].w + d[now] < d[to]) {
        d[to] = e[i].w + d[now];
        if (!vis[to]) {
          if (++cnt[to] >= n) return 0;
          q.push(to);
          vis[to] = 1;
        }
      }
    }
  }
  return 1;
}
int main() {
  int kase;
  scanf("%d", &kase);
  while (kase--) {
    int n, m;
    scanf("%d%d", &n, &m);
    int x, y;
    i64 w;
    _for(i, 1, m) {
      scanf("%d%d%lld", &x, &y, &w);
      addEdge(x, y, w);
      if (w >= 0) addEdge(y, x, w);
    }
    puts(spfa(n, 1) ? "NO" : "YES");
  __end_kase:;
    cnt_edge = 0;
    _set_nul_n(head, n + 1);
  }
FINISHED:
  return 0;
}
