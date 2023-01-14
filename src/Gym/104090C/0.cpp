#include <bits/stdc++.h>
using ll = long long;
#define for_(i, l, r, v...) for (ll i = (l), i##e = (r), ##v; i <= i##e; ++i)
#define rfor_(i, r, l, v...) for (ll i = (r), i##e = (l), ##v; i >= i##e; --i)
#define Rep for_
#define rep rfor_
template <class Tp>
Tp dec(Tp &i) {
  return --i;
}
template <class Tp>
Tp inc(Tp &i) {
  return ++i;
}
using namespace std;
void solve(int t_ = 0) {
  int n, k;
  cin >> n >> k;
  vector<int> p(n + 1);
  vector<vector<int>> w(n + 1, vector<int>(11));
  int s = 0, sp = 0;
  Rep(i, 1, n) {
    cin >> p[i];
    Rep(j, 1, p[i]) cin >> w[i][j];
    s += w[i][p[i]], sp += p[i];
  }
  if (sp <= k) {
    cout << s;
    return;
  }
  vector<vector<array<int, 2>>> Dp(
    n + 1, vector<array<int, 2>>(k + 1, array<int, 2>{-300000000, -300000000}));
  auto ckmax = [](int &a, int b) {
    if (b > a) a = b;
  };
  Rep(i, 0, n) Dp[i][0] = {0, 0};
  Rep(i, 1, n) {
    rep(j, k, 0) {
      Dp[i][j][0] = Dp[i - 1][j][0];
      Dp[i][j][1] = Dp[i - 1][j][1];
      if (j >= p[i])
        ckmax(Dp[i][j][0], Dp[i - 1][j - p[i]][0] + w[i][p[i]]),
          ckmax(Dp[i][j][1], Dp[i - 1][j - p[i]][1] + w[i][p[i]]);
      Rep(q, 1, p[i] - 1)
        if (j >= q) ckmax(Dp[i][j][1], Dp[i - 1][j - q][0] + w[i][q]);
    }
  }
  cout << max(Dp[n][k][0], Dp[n][k][1]);
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  solve(i_);
  return 0;
}
