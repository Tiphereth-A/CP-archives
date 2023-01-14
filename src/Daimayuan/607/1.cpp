#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _rfor(i, r, l, vals...)                                      \
  for (make_signed_t<decltype(r - l)> i = (r), i##end = (l), ##vals; \
       i >= i##end;                                                  \
       --i)
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
  _rfor(i, max_a, 1)
    for (int j = i, d; j <= max_a; j += i) {
      if ((d = abs(j / i - i)) & 1) continue;
      ans += 1ll * cnt[j] * cnt[d / 2];
    }
  cout << ans;
  return 0;
}
