#include <bits/stdc++.h>
const int N = 3e4 + 1;
int fa[N], sum[N], num[N];
int abs(int a) {
  int m = a >> 31;
  return (a + m) ^ m;
}
int find(int x) {
  if (x == fa[x]) return x;
  int fx = find(fa[x]);
  sum[x] += sum[fa[x]];
  return fa[x] = fx;
}
int main() {
  int t, x, y, fx, fy;
  scanf("%d\n", &t);
  for (int i = 1; i <= 30000; ++i) {
    fa[i] = i;
    num[i] = 1;
  }
  char op;
  while (t--) {
    op = getchar();
    scanf(" %d %d\n", &x, &y);
    fx = find(x);
    fy = find(y);
    if (op == 'M') {
      sum[fx] += num[fy];
      num[fy] += num[fx];
      num[fx] = 0;
      fa[fx] = fy;
    } else printf("%d\n", fx != fy ? -1 : abs(sum[x] - sum[y]) - 1);
  }
  return 0;
}
