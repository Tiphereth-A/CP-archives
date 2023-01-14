#include <bits/stdc++.h>
using namespace std;
const int N = 2e3 + 5, MOD = 1e9 + 7;
i64 dp[N][N];
int s[N], t[N];
int main() {
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) cin >> s[i];
  for (int i = 1; i <= m; ++i) cin >> t[i];
  for (int i = 0; i <= n; ++i) dp[i][0] = 1;
  for (int i = 1; i <= m; ++i) dp[0][i] = 1;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      dp[i][j] =
        ((dp[i][j - 1] + dp[i - 1][j] - (s[i] == t[j] ? 0 : dp[i - 1][j - 1])) %
           MOD +
         MOD) %
        MOD;
  cout << dp[n][m];
  return 0;
}
