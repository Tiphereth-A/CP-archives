#include <bits/stdc++.h>
using namespace std;
const int OFFSET = 5, N = 1e4 + OFFSET;
int a[N], sum[N];
int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + a[i];
  int ans = INT_MAX;
  for (int i = 1; i < n; ++i) ans = min(ans, abs(sum[n] - 2 * sum[i]));
  cout << ans;
  return 0;
}
