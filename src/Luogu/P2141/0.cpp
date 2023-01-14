#include <bits/stdc++.h>
bool t[200015], g[200015];
int a[115];
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", a + i);
    g[a[i]] = 1;
  }
  for (int i = 1; i < n; ++i) {
    for (int j = i + 1; j <= n; ++j) ++t[a[i] + a[j]];
  }
  int ans = 0;
  for (int i = 1; i <= 200002; ++i)
    if (t[i] && g[i]) ++ans;
  printf("%d\n", ans);
  return 0;
}
