#include <bits/stdc++.h>
int n, a[105], sum;
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", a + i);
    sum += a[i];
  }
  std::sort(a + 1, a + n + 1);
  printf("%d",
         (n & 1) ?
           int(abs(1.0 * sum / n - a[n / 2 + 1])) :
           int(abs(1.0 * sum / n - 1.0 * (a[n / 2 + 1] + a[n / 2]) / 2)));
  return 0;
}
