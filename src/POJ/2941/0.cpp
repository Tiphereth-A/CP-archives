#include <cstdio>
int a[1005][1005];
int main() {
  int n;
  while (~scanf("%d", &n) && n) {
    bool f = 1;
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j) scanf("%d", &a[i][j]);
    for (int i = 1; f && i < n; ++i)
      for (int j = 1; f && j < n; ++j)
        if (a[i][j] + a[i + 1][j + 1] != a[i][j + 1] + a[i + 1][j]) f = 0;
    puts(f ? "homogeneous" : "not homogeneous");
  }
  return 0;
}
