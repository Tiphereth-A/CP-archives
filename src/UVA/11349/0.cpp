#include <cstdio>
long long M[101][101];
int main() {
  int T;
  while (~scanf("%d", &T))
    for (int t = 1; t <= T; ++t) {
      int n;
      scanf("\nN = %d\n", &n);
      for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) scanf("%lld", &M[i][j]);
      bool f = 1;
      for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
          if (M[i][j] < 0 || M[i][j] != M[n - 1 - i][n - 1 - j]) {
            f = 0;
            goto __end;
          }
    __end:
      printf("Test #%d: %s\n", t, f ? "Symmetric." : "Non-symmetric.");
    }
  return 0;
}
