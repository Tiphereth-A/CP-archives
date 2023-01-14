#include <bits/stdc++.h>
using namespace std;
const int N = 5e3 + 505;
int n, w, s;
i64 a[N];
i64 dp[2][N << 1], ans;
i64 num[N << 1], deq[N << 1];
i64 b[N << 1];
int _pos;
void solve() {
  i64 l = 0, r = 0;
  i64 k = s + 1;
  memset(deq, 0, sizeof(deq));
  memset(b, 0xaf, sizeof(b));
  for (i64 i = 0; i <= w + s; ++i) {
    while (l < r && num[deq[r - 1]] <= num[i]) --r;
    deq[r++] = i;
    if (i - k + 1 >= 0) {
      b[i - k + 1] = num[deq[l]];
      if (deq[l] == i - k + 1) ++l;
    }
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> w >> s;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  memset(dp, 0xaf, sizeof(dp));
  ans = dp[0][0];
  dp[0][0] = 0;
  _pos = 1;
  for (int i = 1; i <= n; ++i) {
    memset(dp[_pos], 0xaf, sizeof(dp[_pos]));
    for (int j = 0; j <= w + s + 1; ++j) num[j] = dp[_pos ^ 1][j];
    solve();
    for (int j = 1; j <= w; ++j) dp[_pos][j] = b[j - 1] + a[i] * j;
    _pos ^= 1;
  }
  for (int i = 0; i <= w; ++i) ans = max(dp[n & 1][i], ans);
  cout << ans;
  return 0;
}
