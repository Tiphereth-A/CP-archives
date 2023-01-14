#include <bits/stdc++.h>
const int N = 2e5 + 5;
int n, t, fa[N], dis[N], ans = 0x7fffffff;
int min(int x, int y) {
  int m = (x - y) >> 31;
  return (x & m) | (y & ~m);
}
int find(int x) {
  if (x != fa[x]) {
    int tmp = fa[x];
    fa[x] = find(fa[x]);
    dis[x] += dis[tmp];
  }
  return fa[x];
}
void merge(int x, int y) {
  int fx = find(x), fy = find(y);
  if (fx != fy) {
    fa[fx] = fy;
    dis[x] = dis[y] + 1;
  } else ans = min(ans, dis[x] + dis[y] + 1);
}
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) fa[i] = i;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &t);
    merge(i, t);
  }
  printf("%d", ans);
  return 0;
}
