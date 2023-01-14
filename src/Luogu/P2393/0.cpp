#include <bits/stdc++.h>
long double a, sum;
int main() {
  while (scanf("%Lf", &a) != EOF) sum += a * 1e6;
  printf("%.5Lf", sum / 1e6);
  return 0;
}
