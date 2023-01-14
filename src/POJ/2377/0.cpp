#include <algorithm>
#include <cstdio>
using namespace std;
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
const int OFFSET = 5;
const int N = 2e3 + OFFSET, M = 4e4 + OFFSET;
struct Edge {
  long long w;
  int from, to;
  Edge(long long _w = 0, int _from = 0, int _to = 0)
    : w(_w), from(_from), to(_to) {}
  bool operator<(const Edge &other) const { return w > other.w; }
} e[M];
int cnt_edge;
void addEdge(int x, int y, long long w = 1) { e[++cnt_edge] = Edge(w, x, y); }
int fa[N];
int find(int x) { return x == fa[x] ? fa[x] : fa[x] = find(fa[x]); }
void merge(int x, int y) { fa[find(x)] = find(y); }
long long kruskal(int n, int k = 1) {
  sort(e + 1, e + cnt_edge + 1);
  for (int i = 0; i <= n; ++i) fa[i] = i;
  int cnt = 0;
  long long ans = 0;
  for (int i = 1, fx, fy; i <= cnt_edge; ++i) {
    fx = find(e[i].from);
    fy = find(e[i].to);
    if (fx == fy) continue;
    fa[fx] = fy;
    ++cnt;
    ans += e[i].w;
    if (cnt == n - k) break;
  }
  if (cnt != n - k) return -1;
  return ans;
}
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  int x, y, z;
  _for(i, 1, m) {
    scanf("%d%d%d", &x, &y, &z);
    addEdge(x, y, z);
    addEdge(y, x, z);
  }
  printf("%lld", kruskal(n));
  return 0;
}
