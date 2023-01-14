#include <bits/stdc++.h>
using namespace std;
const int N = 40, M = (1 << (N / 2)), OFS = 5;
int a[N + OFS];
i64 b[M + OFS];
int main() {
  int n, t;
  cin >> n >> t;
  for (int i = 0; i < n; ++i) cin >> a[i];
  int len = n / 2, len_b = 0;
  i64 ans = 0;
  for (int i = 0; i < (1 << len); ++i) {
    i64 sum = 0;
    for (int j = 0; j < len; ++j)
      if (i >> j & 1) sum += a[j];
    if (sum > t) continue;
    b[len_b++] = sum;
    ans = max(ans, sum);
  }
  sort(b, b + len_b);
  for (int i = 0; i < (1 << (n - len)); ++i) {
    i64 sum = 0;
    for (int j = 0; j < n - len; ++j)
      if (i >> j & 1) sum += a[len + j];
    if (sum > t) continue;
    ans = max(ans, sum);
    int pos = upper_bound(b, b + len_b, t - sum) - b - 1;
    if (pos) ans = max(ans, sum + b[pos]);
  }
  cout << ans;
  return 0;
}
