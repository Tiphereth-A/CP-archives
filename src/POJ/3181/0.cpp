#include <cstdio>
#include <cstring>
const unsigned long long M = 1e18;
long long a[105][1001], b[105][1001];
int main() {
  int n, k;
  while (~scanf("%d%d", &n, &k)) {
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    for (int i = 0; i <= k; ++i) b[i][0] = 1;
    for (int i = 1; i <= k; ++i)
      for (int j = 1; j <= n; ++j) {
        a[i][j] =
          j >= i ? a[i - 1][j] + a[i][j - i] + (b[i - 1][j] + b[i][j - i]) / M :
                   a[i - 1][j];
        b[i][j] = j >= i ? (b[i - 1][j] + b[i][j - i]) % M : b[i - 1][j];
      }
    if (a[k][n]) printf("%lld", a[k][n]);
    printf("%lld\n", b[k][n]);
  }
  return 0;
}
