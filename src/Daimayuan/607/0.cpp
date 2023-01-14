#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
const uint32_t N = 1e6 + 5;
int a[N];
int cnt[N];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n;
  cin >> n;
  _for(i, 1, n) cin >> a[i];
  _for(i, 1, n) ++cnt[a[i]];
  int max_a = 0;
  _for(i, 1, n) chkmax(max_a, a[i]);
  i64 ans = 0;
  _for(i, 1, n)
    for (int j = 1; (2 * a[i] + j) * j <= max_a; ++j)
      ans += cnt[(2 * a[i] + j) * j];
  cout << ans;
  return 0;
}
