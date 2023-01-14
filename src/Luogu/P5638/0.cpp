#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int N = 1e6 + 5;
i64 a[N], b[N], c[N];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  i64 n, k;
  cin >> n >> k;
  for (int i = 1; i < n; ++i) cin >> a[i];
  for (int i = 1; i < n; ++i) b[i] = b[i - 1] + a[i];
  for (int i = n; i; --i) c[i] = c[i + 1] + a[i];
  i64 idx, ans = 0x3f3f3f3f3f3f3f3f;
  for (int i = 1; i <= n; ++i)
    ans = min(ans, b[i - 1] + c[idx = min(n, i + k)]);
  cout << ans;
  return 0;
}
