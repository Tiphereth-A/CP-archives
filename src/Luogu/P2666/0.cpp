#include <bits/stdc++.h>
int sqr[110], n, f, ans;
int a[5];
bool app[10005];
void dfs(int p, int sum) {
  if (sum > n) return;
  if (p == 3 && !app[n - sum]) return;
  if (p == 4 && n == sum) {
    ans++;
    return;
  }
  if (p > 4) return;
  int f2 = sqrt(n - sum);
  for (int i = 0; i <= f2; i++) dfs(p + 1, sum + sqr[i]);
}
int main() {
  scanf("%d", &n);
  f = sqrt(n);
  for (int i = 0; i <= f; i++) {
    sqr[i] = i * i;
    app[i * i] = true;
  }
  dfs(0, 0);
  printf("%d", ans);
  return 0;
}
