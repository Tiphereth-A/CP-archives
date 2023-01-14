#include <bits/stdc++.h>
const int N = 3e4 + 5;
int fa[N], sum[N], num[N];
int abs(int a) {
  int m = a >> 31;
  return (a + m) ^ m;
}
int find(int x) {
  if (x == fa[x]) return x;
  int fa_x = find(fa[x]);
  sum[x] += sum[fa[x]];
  return fa[x] = fa_x;
}
int main() {
  int t;
  scanf("%d\n", &t);
  for (int i = 1; i <= 30000; ++i) {
    fa[i] = i;
    num[i] = 1;
  }
  while (t--) {
    char op = getchar();
    int x, y;
    scanf(" %d %d\n", &x, &y);
    int fa_x = find(x), fa_y = find(y);
    if (op == 'M') {
      sum[fa_x] += num[fa_y];
      num[fa_y] += num[fa_x];
      num[fa_x] = 0;
      fa[fa_x] = fa_y;
    } else printf("%d\n", fa_x != fa_y ? -1 : abs(sum[x] - sum[y]) - 1);
  }
  return 0;
}
