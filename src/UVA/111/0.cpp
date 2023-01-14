#include <bits/stdc++.h>
using namespace std;
int dp[25][25], a[25], __[25];
int main() {
  int n, _;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> _;
    a[_ - 1] = i;
  }
  while (cin >> _) {
    __[_ - 1] = 0;
    for (int i = 1; i < n; ++i) {
      cin >> _;
      __[_ - 1] = i;
    }
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        dp[i + 1][j + 1] =
          a[j] == __[i] ? dp[i][j] + 1 : max(dp[i][j + 1], dp[i + 1][j]);
    cout << dp[n][n] << endl;
  }
  return 0;
}
