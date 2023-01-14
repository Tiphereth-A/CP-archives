#include <bits/stdc++.h>
using namespace std;
const int N = 210;
int a[N], s[N], f[N][N], g[N][N];
int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i], a[i + n] = a[i];
  for (int i = 1; i <= 2 * n; i++) s[i] = s[i - 1] + a[i];
  for (int len = 2; len <= n; len++) {
    for (int l = 1; l + len - 1 <= 2 * n; l++) {
      int r = l + len - 1;
      f[l][r] = 0x3f3f3f;
      for (int k = l; k < r; k++) {
        f[l][r] = min(f[l][r], f[l][k] + f[k + 1][r] + s[r] - s[l - 1]);
        g[l][r] = max(g[l][r], g[l][k] + g[k + 1][r] + s[r] - s[l - 1]);
      }
    }
  }
  int res1 = 0x3f3f3f, res2 = 0;
  for (int i = 1; i <= n; i++) {
    res1 = min(res1, f[i][i + n - 1]);
    res2 = max(res2, g[i][i + n - 1]);
  }
  cout << res1 << endl << res2;
  return 0;
}
