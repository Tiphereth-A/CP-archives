#include <bits/stdc++.h>
const int N = 1e4 + 5;
bool sum[N];
int n, m;
int main() {
  std::cin >> n >> m;
  memset(sum, 1, sizeof(bool) * (n + 1));
  while (m--) {
    int x, y;
    std::cin >> x >> y;
    memset(sum + x, 0, sizeof(bool) * (y - x + 1));
  }
  int ans = 0;
  for (int i = 0; i <= n; ++i) { ans += sum[i]; }
  std::cout << ans;
  return 0;
}
