#include <bits/stdc++.h>
int n, sum, c[15], a[15], v[15];
bool dfs(int step, int i, int s) {
  if (s > sum) return 0;
  if (step == n) {
    if (s == sum) {
      a[step] = i;
      return 1;
    }
    return 0;
  }
  v[i] = 1;
  for (int j = 1; j <= n; j++) {
    if (!v[j] && dfs(step + 1, j, s + c[step] * j)) {
      a[step] = i;
      return 1;
    }
  }
  v[i] = 0;
  return 0;
}
int main() {
  scanf("%d%d", &n, &sum);
  c[0] = c[n - 1] = 1;
  for (int i = 1; i <= (n >> 1); i++)
    c[i] = c[n - i - 1] = (n - i) * c[i - 1] / i;
  if (dfs(0, -1, 0))
    for (int i = 1; i <= n; i++) printf("%d ", a[i]);
  return 0;
}
