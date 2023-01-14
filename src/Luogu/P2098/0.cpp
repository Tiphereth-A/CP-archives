#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 9;
const int N = 1005;
int dp[11][N][N];
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, m, k;
  cin >> n >> m >> k;
  vector<int> a(n + 1), b(m + 1);
  for (int i = 1; i <= n; ++i) cin >> a[i];
  for (int i = 1; i <= m; ++i) cin >> b[i];
  sort(a.begin() + 1, a.end());
  sort(b.begin() + 1, b.end());
  for (int i = 0; i <= n; ++i)
    for (int j = 0; j <= m; ++j) dp[0][i][j] = 1;
  for (int l = 1; l <= k; ++l)
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j)
        dp[l][i][j] = ((dp[l][i - 1][j] + dp[l][i][j - 1]) % MOD +
                       ((MOD - dp[l][i - 1][j - 1]) +
                        (a[i] > b[j]) * dp[l - 1][i - 1][j - 1]) %
                         MOD) %
                      MOD;
  cout << dp[k][n][m] << '\n';
  return 0;
}
