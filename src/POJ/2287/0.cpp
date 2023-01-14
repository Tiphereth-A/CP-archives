#include <algorithm>
#include <cstdio>
#include <functional>
const int N = 1005;
int g[N], k[N];
int main() {
  int n;
  while (scanf("%d", &n) && n) {
    for (int i = 1; i <= n; ++i) scanf("%d", g + i);
    for (int i = 1; i <= n; ++i) scanf("%d", k + i);
    std::sort(g + 1, g + n + 1, std::greater<int>());
    std::sort(k + 1, k + n + 1, std::greater<int>());
    int ans = 0;
    int l_g = 1, l_k = 1, r_g = n, r_k = n;
    while (l_g <= r_g && l_k <= r_k) {
      if (g[l_g] > k[l_k]) ++l_k, ++l_g, ++ans;
      else if (g[l_g] < k[l_k]) ++l_k, --r_g, --ans;
      else if (g[r_g] > k[r_k]) --r_k, --r_g, ++ans;
      else ++l_k, --r_g, ans -= g[r_g + 1] < k[l_k - 1] ? 1 : 0;
    }
    printf("%d\n", ans * 200);
  }
  return 0;
}
