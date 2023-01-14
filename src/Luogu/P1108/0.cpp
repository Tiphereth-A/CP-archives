#include <bits/stdc++.h>
int n, p[5005], f[5005], t[5005], ans, ansn;
int max(int x, int y) { return x > y ? x : y; }
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", p + i);
    int *tmp = &f[i];
    for (int j = 1; j < i; ++j)
      if (p[i] < p[j]) (*tmp) = max((*tmp), f[j] + 1);
    if (!(*tmp)) ++(*tmp);
    if ((*tmp) > ans) ans = (*tmp);
    for (int j = 1; j < i; ++j)
      if (f[i] == f[j] && p[i] == p[j]) t[j] = 0;
      else if (f[i] == f[j] + 1 && p[i] < p[j]) t[i] += t[j];
    if (!t[i]) t[i] = 1;
  }
  for (int i = 1; i <= n; ++i)
    if (f[i] == ans) ansn += t[i];
  printf("%d %d", ans, ansn);
  return 0;
}
