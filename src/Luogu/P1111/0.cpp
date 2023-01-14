#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
const int M = 100005;
const int N = 1005;
int n, m, tot;
struct f {
  int x, y, t;
} g[M];
int pre[N];
bool cmp(f a, f b) { return a.t < b.t; }
int find(int x) {
  int a = x;
  while (a != pre[a]) a = pre[a];
  int b = x, c;
  while (b != a) {
    c = pre[b];
    pre[b] = a;
    b = c;
  }
  return a;
}
bool ins(int x, int y) {
  if (find(x) != find(y)) {
    pre[find(x)] = find(y);
    return true;
  }
  return false;
}
int main() {
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= m; i++) scanf("%d %d %d", &g[i].x, &g[i].y, &g[i].t);
  std::sort(g + 1, g + m + 1, cmp);
  _for(i, 1, n) pre[i] = i;
  tot = n;
  _for(i, 1, m) {
    if (find(g[i].x) != find(g[i].y)) {
      ins(g[i].x, g[i].y);
      tot--;
    }
    if (tot == 1) {
      printf("%d\n", g[i].t);
      return 0;
    }
  }
  printf("-1\n");
  return 0;
}
