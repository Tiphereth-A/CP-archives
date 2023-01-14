#include <bits/stdc++.h>
using namespace std;
using pii = pair<i64, i64>;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
const int OFFSET = 5;
const int N = 1e3 + OFFSET, M = 2e6 + OFFSET, K = 21;
struct Edge {
  double w;
  int from, to;
  bool operator<(const Edge &other) const { return w < other.w; }
} e[M];
int cnt_edge;
void addEdge(int x, int y, double w = 1) { e[++cnt_edge] = {w, x, y}; }
int fa[N];
int find(int x) { return x == fa[x] ? fa[x] : fa[x] = find(fa[x]); }
void merge(int x, int y) { fa[find(x)] = find(y); }
double kruskal(int n, int k = 1) {
  sort(e + 1, e + cnt_edge + 1);
  _for(i, 1, n) fa[i] = i;
  int cnt = 0;
  double ans = 0;
  for (int i = 1, fx, fy; i <= cnt_edge; ++i) {
    fx = find(e[i].from);
    fy = find(e[i].to);
    if (fx == fy) continue;
    fa[fx] = fy;
    ++cnt;
    ans += e[i].w;
    if (cnt == n - k) break;
  }
  return ans;
}
pii point[N];
double dis(int x, int y) {
  return sqrt(
    (point[x].first - point[y].first) * (point[x].first - point[y].first) +
    (point[x].second - point[y].second) * (point[x].second - point[y].second));
}
bool vis[N];
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  _for(i, 1, n) scanf("%d%d", &point[i].first, &point[i].second);
  _for(i, 1, n) fa[i] = i;
  int x, y;
  _for(i, 1, m) {
    scanf("%d%d", &x, &y);
    merge(x, y);
  }
  _for(i, 1, n)
    _for(j, 1, n) {
      if (find(i) == find(j)) {
        addEdge(i, j, 0);
        addEdge(j, i, 0);
      } else {
        addEdge(i, j, dis(i, j));
        addEdge(j, i, dis(i, j));
      }
    }
  printf("%.2lf", kruskal(n));
FINISHED:
  return 0;
}
