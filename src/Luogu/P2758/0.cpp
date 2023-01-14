#include <bits/stdc++.h>
using namespace std;
const int N = 2005;
string a, b;
int dp[N][N];
int main() {
  cin >> a >> b;
  a = " " + a;
  b = " " + b;
  for (int i = 1; i < a.size(); ++i) dp[i][0] = i;
  for (int j = 1; j < b.size(); ++j) dp[0][j] = j;
  for (int i = 1; i < a.size(); ++i)
    for (int j = 1; j < b.size(); ++j) {
      if (a[i] == b[j]) dp[i][j] = dp[i - 1][j - 1];
      else
        dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
    }
  cout << dp[a.size() - 1][b.size() - 1];
  return 0;
}
