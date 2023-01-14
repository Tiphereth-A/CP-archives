#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
i64 a[33];
set<i64> s[65];
int main() {
  int kase;
  cin >> kase;
  while (kase--) {
    int n;
    cin >> n;
    _for(i, 0, n - 1) cin >> a[i];
    int mid = (n + 1) / 2;
    _for(i, 0ll, (1 << mid) - 1, sum, cnt) {
      sum = cnt = 0;
      _for(j, 0, mid - 1) {
        if (i & (1 << j)) {
          sum += a[j];
          ++cnt;
        } else {
          sum -= a[j];
          --cnt;
        }
      }
      s[cnt + n].insert(sum);
    }
    i64 ans = INT64_MAX;
    _for(i, 0ll, (1 << (n - mid)) - 1, sum, cnt) {
      sum = cnt = 0;
      _for(j, 0, n - mid - 1) {
        if (!(i & (1 << j))) {
          sum += a[j + mid];
          ++cnt;
        } else {
          sum -= a[j + mid];
          --cnt;
        }
      }
      if (n % 2) {
        if (s[cnt + 1 + n].size()) {
          auto it1 = s[cnt + 1 + n].lower_bound(sum),
               it2 = s[cnt + 1 + n].upper_bound(sum);
          if (it1 != s[cnt + 1 + n].end()) ans = min(ans, abs(*it1 - sum));
          if (it2 != s[cnt + 1 + n].end()) ans = min(ans, abs(*it2 - sum));
        }
        if (s[cnt - 1 + n].size()) {
          auto it1 = s[cnt - 1 + n].lower_bound(sum),
               it2 = s[cnt - 1 + n].upper_bound(sum);
          if (it1 != s[cnt - 1 + n].end()) ans = min(ans, abs(*it1 - sum));
          if (it2 != s[cnt - 1 + n].end()) ans = min(ans, abs(*it2 - sum));
        }
      } else if (s[cnt + n].size()) {
        auto it1 = s[cnt + n].lower_bound(sum),
             it2 = s[cnt + n].upper_bound(sum);
        if (it1 != s[cnt + n].end()) ans = min(ans, abs(*it1 - sum));
        if (it2 != s[cnt + n].end()) ans = min(ans, abs(*it2 - sum));
      }
    }
    cout << ans << '\n';
    for (int i = 0; i < 65; ++i) s[i].clear();
  }
  return 0;
}
