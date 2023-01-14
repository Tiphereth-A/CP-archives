#include <bits/stdc++.h>
int main() {
  double n;
  scanf("%lf", &n);
  printf("%.12f", n * (n + 1) / (2 * (2 * n - 1)));
  return 0;
}
