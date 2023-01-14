#include <bits/stdc++.h>
const int N = 1e7 + 5;
int n, a[N];
double ans;
int main() {
  int A, B, C;
  scanf("%d%d%d%d%d", &n, &A, &B, &C, a + 1);
  for (int i = 2; i <= n; i++) a[i] = ((long long)a[i - 1] * A + B) % 100000001;
  for (int i = 1; i <= n; i++) a[i] = a[i] % C + 1;
  a[n + 1] = a[1];
  for (int i = 1; i <= n; i++) ans += 1.0 / (a[i] > a[i + 1] ? a[i] : a[i + 1]);
  printf("%.3lf", ans);
  return 0;
}
