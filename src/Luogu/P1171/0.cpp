#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
using std::min;
const int N = 20;
int n;
int map[N][N], f[1 << N][N];
int main() {
  memset(f, 0x3f, sizeof f);
  f[1][0] = 0;
  cin >> n;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j) cin >> map[i][j];
  for (int i = 1; i < (1 << n); i += 2)
    for (int j = 0; j < n; ++j) {
      if (!((i >> j) & 1)) continue;
      for (int k = 0; k < n; ++k) {
        if (j == k || !((i >> k) & 1)) continue;
        f[i][j] = min(f[i][j], f[i ^ (1 << j)][k] + map[k][j]);
      }
    }
  int ans = 0x3f3f3f3f;
  for (int i = 0; i < n; ++i) {
    ans = min(ans, f[(1 << n) - 1][i] + map[i][0]);
  }
  cout << ans;
  return 0;
}
