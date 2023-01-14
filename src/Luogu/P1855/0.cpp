#include <bits/stdc++.h>
using namespace std;
int dp[1010][1010];
int a[1010], b[1010];
int main() {
  int n, m, t;
  cin >> n >> m >> t;
  for (int i = 1; i <= n; i++) {
    cin >> a[i] >> b[i];
    for (int j = m; j >= a[i]; j--)
      for (int k = t; k >= b[i]; k--)
        dp[j][k] = max(dp[j][k], dp[j - a[i]][k - b[i]] + 1);
  }
  cout << dp[m][t];
}
