#include <algorithm>
#include <cstdio>
#include <functional>
int a[1000005];
int main() {
  int n, m;
  while (~scanf("%d%d", &n, &m)) {
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    std::partial_sort(a + 1, a + m + 1, a + n + 1, std::greater<int>());
    for (int i = 1; i <= m; ++i) printf("%d%c", a[i], " \n"[i == m]);
  }
}
