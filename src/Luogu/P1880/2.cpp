#include <bits/stdc++.h>
using namespace std;
const int N = 205;
int dp[N][N], sum[N / 2], a[N];
int main() {
#define __(op)                                            \
  for (int len = 2; len <= n; ++len)                      \
    for (int l = 1, r; l <= 2 * n - len + 1; ++l) {       \
      r = l + len - 1;                                    \
      for (int k = l; k < r; ++k)                         \
        dp[l][r] = op(dp[l][r], dp[l][k] + dp[k + 1][r]); \
      dp[l][r] += sum[r] - sum[l - 1];                    \
    }                                                     \
  for (int i = 1; i <= n; ++i) ans_##op = op(ans_##op, dp[i][i + n - 1]);
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    a[n + i] = a[i];
  }
  for (int i = 1; i <= 2 * n; ++i) sum[i] = sum[i - 1] + a[i];
  int ans_max = INT32_MIN;
  memset(dp, 0x80, sizeof(dp));
  for (int i = 0; i <= 2 * n; ++i) dp[i][i] = 0;
  __(max);
  int ans_min = INT32_MAX;
  memset(dp, 0x7f, sizeof(dp));
  for (int i = 0; i <= 2 * n; ++i) dp[i][i] = 0;
  __(min);
  cout << ans_min << endl << ans_max;
  return 0;
}
