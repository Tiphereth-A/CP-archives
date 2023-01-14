#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _rfor(i, r, l, vals...)                                      \
  for (make_signed_t<decltype(r - l)> i = (r), i##end = (l), ##vals; \
       i >= i##end;                                                  \
       --i)
#define _all(a) (a).begin(), (a).end()
const array<array<i64, 10>, 10> dp([]() {
  array<array<i64, 10>, 10> dp;
  fill(_all(dp[0]), 1);
  _for(i, 1, 9) fill(_all(dp[i]), 0);
  _for(i, 1, 9)
    _for(j, 0, 9)
      _for(k, 0, 9) {
        if (abs(j - k) < 2) continue;
        dp[i][j] += dp[i - 1][k];
      }
  return dp;
}());
auto f = [](int x) -> i64 {
  vector<int> digit;
  while (x) {
    digit.push_back(x % 10);
    x /= 10;
  }
  i64 ret = 0;
  _for(i, 0, (int)digit.size() - 2)
    ret += accumulate(dp[i].begin() + 1, dp[i].end(), 0);
  ret += accumulate(dp[digit.size() - 1].begin() + 1,
                    dp[digit.size() - 1].begin() + digit.back(),
                    0);
  _rfor(i, (int)digit.size() - 2, 0) {
    _for(j, 0, digit[i] - 1)
      if (abs(j - digit[i + 1]) >= 2) ret += dp[i][j];
    if (abs(digit[i + 1] - digit[i]) < 2) break;
  }
  return ret;
};
auto solve() -> void {
  int l, r;
  cin >> l >> r;
  cout << f(r + 1) - f(l);
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
