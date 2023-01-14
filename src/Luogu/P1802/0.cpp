#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 5;
int v[N], w[N];
long long dp[N];
int main() {
  int n, m;
  cin >> n >> m;
  long long ans = 0;
  for (int i = 1, lose, win; i <= n; ++i) {
    cin >> lose >> win >> w[i];
    v[i] = win - lose;
    ans += lose;
  }
  for (int i = 1; i <= n; ++i)
    for (int j = m; j >= w[i]; --j)
      if (j - w[i] >= 0) dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
  long long _ = 0;
  for (int i = 0; i <= m; ++i) _ = max(_, dp[i]);
  cout << (ans + _) * 5;
  return 0;
}
