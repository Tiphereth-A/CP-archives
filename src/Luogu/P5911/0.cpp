#include <bits/stdc++.h>
using ll = long long;
template <class T>
using vc = std::vector<T>;
#define for_(i, l, r, v...) for (ll i = (l), i##e = (r), ##v; i <= i##e; ++i)
template <typename... Ts>
void dec(Ts &...x) {
  ((--x), ...);
}
template <typename... Ts>
void inc(Ts &...x) {
  ((++x), ...);
}
using namespace std;
void solve(int t_ = 0) {
  int W, n;
  cin >> W >> n;
  const int S = (1 << n) - 1;
  vc<int> ts(S + 1), ws(S + 1);
  {
    vc<int> t(n), w(n);
    for_(i, 0, n - 1) cin >> t[i] >> w[i];
    for_(i, 0, S)
      for_(j, 0, n - 1)
        if (i & (1 << j)) {
          ts[i] = max(ts[i], t[j]);
          ws[i] += w[j];
        }
  }
  vc<int> dp(S + 1, numeric_limits<int>::max() / 2);
  dp[0] = 0;
  for_(i, 0, S)
    for (int j = i;; j = i & (j - 1)) {
      if (ws[i ^ j] <= W) dp[i] = min(dp[i], dp[j] + ts[i ^ j]);
      if (!j) break;
    }
  cout << dp[S] << '\n';
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  solve(i_);
  return 0;
}
