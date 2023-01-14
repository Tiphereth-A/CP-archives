#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
const uint32_t N = 2e5 + 5;
map<i64, int> mp;
i64 a[N], s[N];
int main() {
  int n, k;
  cin >> n >> k;
  _for(i, 1, n) cin >> a[i];
  _for(i, 1, n) s[i] = ((s[i - 1] + a[i] - 1) % k + k) % k;
  i64 ans = 0, l = 0;
  mp[0] = 1;
  _for(i, 1, n) {
    if (l <= i - k) {
      if (mp[s[l]] > 0) --mp[s[l]];
      ++l;
    }
    ans += mp[s[i]]++;
  }
  cout << ans;
  return 0;
}
