#include <algorithm>
#include <cstdio>
int a[1000005];
int main() {
  int n;
  while (~scanf("%d", &n)) {
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    std::sort(a + 1, a + n + 1);
    printf("%d\n", a[n / 2 + 1]);
  }
  return 0;
}
