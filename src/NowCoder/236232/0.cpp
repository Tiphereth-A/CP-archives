#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
auto solve() -> void {
  int n, k;
  cin >> n >> k;
  if (k > n) k = n;
  string s;
  cin >> s;
  i64 der = 0, de = 0, er = 0, d = 0, e = 0, r = 0;
  i64 ans = 0;
  _for(i, 0, n - 1) {
    if (s[i] == 'r') {
      der += de;
      er += e;
      ++r;
    } else if (s[i] == 'e') {
      de += d;
      ++e;
    } else if (s[i] == 'd') ++d;
    if (i >= k) {
      if (s[i - k] == 'r') --r;
      else if (s[i - k] == 'e') {
        er -= r;
        --e;
      } else if (s[i - k] == 'd') {
        der -= er;
        de -= e;
        --d;
      }
    }
    ans = max(ans, der);
  }
  cout << ans;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
