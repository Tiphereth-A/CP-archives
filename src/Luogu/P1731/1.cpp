#include <bits/stdc++.h>
using namespace std;
int r[30], h[30], ans = INT_MAX, n, m;
void dfs(int x, int y, int k, int z) {
  if (y < 0 || x > m + 1 || k >= ans || k + z + r[1] * r[1] > ans ||
      y > (r[x - 1]) * (r[x - 1]) * (h[x - 1]) * z)
    return;
  if (y == 0 && x == m + 1) {
    ans = min(ans, k += r[1] * r[1]);
    return;
  }
  for (int i = r[x - 1] - 1; i >= z; --i)
    for (int j = h[x - 1] - 1; j >= z; --j)
      if (y >= i * i * j && x + 1 <= m + 1) {
        r[x] = i;
        h[x] = j;
        dfs(x + 1, y - i * i * j, k + (i * 2 * j), z - 1);
        h[x] = 0;
        r[x] = 0;
      }
}
int main() {
  cin >> n >> m;
  r[0] = h[0] = sqrt(n);
  dfs(1, n, 0, m);
  cout << (ans == INT_MAX ? 0 : ans);
  return 0;
}
