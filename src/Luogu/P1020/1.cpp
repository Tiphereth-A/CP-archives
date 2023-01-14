#include <bits/stdc++.h>
using namespace std;
int n = 0, a[100001], f[100001], d[100001], ans = 1, t = 0;
int main() {
  while (~scanf("%d", &a[++n]));
  n--;
  for (int i = 1; i <= n; i++) {
    f[i] = 1;
    for (int j = t; j > 0; j--)
      if (a[i] <= a[d[j]]) {
        f[i] = f[d[j]] + 1;
        break;
      }
    t = max(t, f[i]);
    d[f[i]] = i;
    ans = max(ans, f[i]);
  }
  printf("%d\n", ans);
  ans = 1;
  t = 0;
  for (int i = 1; i <= n; i++) {
    f[i] = 1;
    for (int j = t; j > 0; j--)
      if (a[i] > a[d[j]]) {
        f[i] = f[d[j]] + 1;
        break;
      }
    t = max(t, f[i]);
    d[f[i]] = i;
    ans = max(ans, f[i]);
  }
  printf("%d", ans);
}
