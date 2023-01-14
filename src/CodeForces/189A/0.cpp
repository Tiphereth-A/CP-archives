#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, a[3];
  cin >> n >> a[0] >> a[1] >> a[2];
  vector<int> dp(n + 1);
  fill(dp.begin() + 1, dp.end(), -1);
  for (int i = 0; i < 3; ++i)
    for (int j = a[i]; j <= n; ++j)
      if (~dp[j - a[i]]) dp[j] = max(dp[j], dp[j - a[i]] + 1);
  cout << dp[n] << '\n';
  return 0;
}
