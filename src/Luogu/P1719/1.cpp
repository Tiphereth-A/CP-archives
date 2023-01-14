#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
const int N = 125;
i64 a[N][N], b[N], dp[N];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n;
  cin >> n;
  _for(i, 1, n)
    _for(j, 1, n) {
      cin >> a[i][j];
      a[i][j] += a[i - 1][j];
    }
  i64 ans = 0;
  _for(i, 1, n)
    _for(j, 0, i - 1) {
      memset(dp, 0, sizeof(dp));
      _for(k, 1, n) b[k] = a[i][k] - a[j][k];
      _for(k, 1, n) ans = max(ans, dp[k] = max(dp[k - 1] + b[k], b[k]));
    }
  cout << ans;
  return 0;
}
