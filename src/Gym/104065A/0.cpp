#include <bits/stdc++.h>
using ll = long long;
#define for_(i, l, r, v...) for (ll i = (l), i##e = (r), ##v; i <= i##e; ++i)
#define Rep for_
template <class Tp>
Tp dec(Tp &i) {
  return --i;
}
template <class Tp>
Tp inc(Tp &i) {
  return ++i;
}
using namespace std;
#define int long long
void solve(int t_ = 0) {
  const int INF = 1e14;
  int n, k;
  cin >> n >> k;
  vector<int> A(2 * n + 1), B(2 * n + 1);
  vector<vector<vector<int>>> Dp(
    2 * n + 2, vector<vector<int>>(k + 2, vector<int>(k + 2, -INF)));
  Rep(i, 1, n) cin >> A[i];
  Rep(i, 1, n) cin >> B[i];
  sort(A.begin() + 1, A.end(), greater<int>());
  sort(B.begin() + 1, B.end(), greater<int>());
  ll Ans = -1e14;
  function<int(int, int, int)> DP = [&](int m, int a, int b) -> int {
    if (m == 2 * n + 1) return 0;
    if (Dp[m][a][b] != -INF) return Dp[m][a][b];
    int Ret;
    if (m & 1) {
      Ret = -INF;
      if (a != k && a != n) Ret = DP(m + 1, a + 1, b) + A[(m / 2) - b + a + 1];
      Ret = max(Ret, DP(m + 1, a, b));
    } else {
      Ret = INF;
      if (b != k && b != n) Ret = DP(m + 1, a, b + 1) - B[(m / 2) - a + b + 1];
      Ret = min(Ret, DP(m + 1, a, b));
    }
    return Dp[m][a][b] = Ret;
  };
  cout << DP(1, 0, 0);
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  solve(i_);
  return 0;
}
