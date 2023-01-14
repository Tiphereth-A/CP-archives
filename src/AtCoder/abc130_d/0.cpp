#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
i64 a[N], sum[N];
int main() {
  int n;
  i64 k;
  cin >> n >> k;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + a[i];
  i64 ans = 0;
  for (int i = n; i; --i) {
    if (sum[i] < k) break;
    ans += upper_bound(sum + 1, sum + n + 1, sum[i] - k) - sum;
  }
  cout << ans;
  return 0;
}
