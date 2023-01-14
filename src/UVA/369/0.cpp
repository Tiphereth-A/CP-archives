#include <cstdio>
long long f[110][110];
int main() {
  int a, b;
  for (int i = 0; i <= 100; ++i) f[i][0] = 1;
  while (~scanf("%d%d", &a, &b) && (a || b)) {
    for (int i = 1; i <= a; ++i)
      for (int j = 1; j <= i; ++j) f[i][j] = f[i - 1][j] + f[i - 1][j - 1];
    printf("%d things taken %d at a time is %lld exactly.\n", a, b, f[a][b]);
  }
  return 0;
}
