#include <cstdio>
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
int p[1000010];
int main() {
  int n, k;
  int e;
  while (~scanf("%d%d", &n, &k)) {
    e = 0;
    for (int i = 1; i <= n; ++i)
      if (gcd(i, n) == 1) p[++e] = i;
    printf("%d\n", p[(k - 1) % e + 1] + (k - 1) / e * n);
  }
  return 0;
}
