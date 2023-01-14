#include <cstdio>
using namespace std;
double f[101][101], ans[101];
int main() {
  for (int i = 1; i <= 105; ++i) {
    for (int j = 1; j <= i; ++j)
      f[i][j] = i == j ? 1 : f[i - 1][j - 1] + f[i - 1][j] * j;
    for (int j = 1; j <= i; ++j) ans[i] += f[i][j];
  }
  int n;
  while (scanf("%d", &n) && n) printf("%d %.0lf\n", n, ans[n]);
}
