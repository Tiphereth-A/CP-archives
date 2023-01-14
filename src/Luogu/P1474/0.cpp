#include <bits/stdc++.h>
using namespace std;
int64_t v, n, h[30], dp[10005] = {1};
int main() {
  cin >> v >> n;
  for (int i = 0; i < v; i++) cin >> h[i];
  for (int i = 0; i < v; i++)
    for (int j = h[i]; j <= n; j++) dp[j] += dp[j - h[i]];
  cout << dp[n];
  return 0;
}
