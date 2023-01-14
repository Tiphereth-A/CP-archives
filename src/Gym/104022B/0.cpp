#include <bits/stdc++.h>
using namespace std;
const int N = 10000 + 7;
int a[N], dp[2][N][10];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  for (int i = 0; i <= n; ++i)
    for (int j = 0; j <= 3; ++j) dp[0][i][j] = dp[1][i][j] = -(1000000000 + 7);
  int Now = 0, Last = 1;
  dp[Now][0][3] = 0;
  for (int i = 1; i <= n; ++i) {
    swap(Now, Last);
    for (int j = 1; j <= i; ++j) {
      dp[Now][j][0] = max(dp[Last][j - 1][3], dp[Last][j][0]);
      dp[Now][j][1] =
        max({dp[Last][j][1], dp[Last][j][0] - a[i], dp[Last][j - 1][3] - a[i]});
      dp[Now][j][2] =
        max({dp[Last][j][2], dp[Last][j][0] + a[i], dp[Last][j - 1][3] + a[i]});
      dp[Now][j][3] = max({dp[Last][j][3],
                           dp[Last][j - 1][3],
                           dp[Last][j][1] + a[i],
                           dp[Last][j][2] - a[i]});
    }
  }
  for (int i = 1; i <= n; ++i) cout << dp[Now][i][3] << '\n';
}
