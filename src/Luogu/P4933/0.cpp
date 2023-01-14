#include <bits/stdc++.h>
using namespace std;
const int N = 1005, M = 4e4 + 5, ofs = 2e4, mod = 998244353;
int a[N];
int dp[N][M];
int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    ++ans;
    for (int j = i - 1; j; --j) {
      (dp[i][ofs + a[i] - a[j]] += dp[j][ofs + a[i] - a[j]] + 1) %= mod;
      (ans += dp[j][ofs + a[i] - a[j]] + 1) %= mod;
    }
  }
  cout << ans;
  return 0;
}
