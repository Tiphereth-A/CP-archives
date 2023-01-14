#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  i64 n, m, k;
  cin >> n >> m >> k;
  if (!k) {
    cout << '0';
    return 0;
  }
  if (n < m) swap(n, m);
  i64 a = min(m, (i64)sqrt(k));
  i64 b = min(n, k / a);
  i64 ans = 0;
  for (i64 s; a >= 2 && b <= n; --a, b = k / a) {
    s = a * (a - 1) / 2 * b * (b - 1) / 2;
    if (i64 t = k - a * b; t > 1) s += (t * (t - 1) * (b < n ? b : a)) / 2;
    ans = max(ans, s);
  }
  cout << ans;
}
