#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
const uint32_t OFFSET = 5;
const uint32_t N = 1e5 + OFFSET;
int l[N], r[N];
auto solve() -> void {
  int n;
  cin >> n;
  _for(i, 1, n) cin >> l[i] >> r[i];
  sort(l + 1, l + n + 1);
  sort(r + 1, r + n + 1);
  i64 ans = n;
  _for(i, 1, n) ans += max(l[i], r[i]);
  cout << ans;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
