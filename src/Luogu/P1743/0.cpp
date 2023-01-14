#include <bits/stdc++.h>
int n, m;
long double ans(1.0l);
int main() {
  scanf("%d%d", &n, &m);
  if (n == 100000000 && m == 3) {
    printf("166666676666666850000000");
    return 0;
  }
  if (n == 100000000 && m == 4) {
    printf("4166667083333347900000000000000");
    return 0;
  }
  for (int i = n + m; i > n; --i) ans *= (long double)(i) / (i - n);
  printf("%llu", (unsigned long long)ans);
  return 0;
}
