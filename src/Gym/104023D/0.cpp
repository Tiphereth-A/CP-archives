#include <bits/stdc++.h>
using ll = long long;
#define int long long
#define Rep(i, a, b) for (int i = (a), i##Limit = (b); i <= i##Limit; ++i)
using namespace std;
const int GO[19][6] = {{1, 3, 4, -1, -1, -1},
                       {4, 5, -1, -1, -1, -1},
                       {1, 5, 6, -1, -1, -1},
                       {4, 8, -1, -1, -1, -1},
                       {5, 8, 9, -1, -1, -1},
                       {4, 9, 10, -1, -1, -1},
                       {5, 10, -1, -1, -1, -1},
                       {3, 8, 12, -1, -1, -1},
                       {4, 9, 13, -1, -1, -1},
                       {4, 5, 8, 10, 13, 14},
                       {5, 9, 14, -1, -1, -1},
                       {6, 10, 15, -1, -1, -1},
                       {8, 13, -1, -1, -1, -1},
                       {8, 9, 14, -1, -1, -1},
                       {9, 10, 13, -1, -1, -1},
                       {10, 14, -1, -1, -1, -1},
                       {12, 13, 17, -1, -1, -1},
                       {13, 14, -1, -1, -1, -1},
                       {14, 15, 17, -1, -1, -1}};
const int GO2[19][6] = {{2, 7, 9, -1, -1, -1},
                        {8, 10, -1, -1, -1, -1},
                        {0, 9, 11, -1, -1, -1},
                        {5, 13, -1, -1, -1, -1},
                        {6, 12, 14, -1, -1, -1},
                        {3, 13, 15, -1, -1, -1},
                        {4, 14, -1, -1, -1, -1},
                        {0, 9, 16, -1, -1, -1},
                        {1, 10, 17, -1, -1, -1},
                        {0, 2, 7, 11, 16, 18},
                        {1, 8, 17, -1, -1, -1},
                        {2, 9, 18, -1, -1, -1},
                        {4, 14, -1, -1, -1, -1},
                        {3, 5, 15, -1, -1, -1},
                        {4, 6, 12, -1, -1, -1},
                        {5, 13, -1, -1, -1, -1},
                        {7, 9, 18, -1, -1, -1},
                        {8, 10, -1, -1, -1, -1},
                        {9, 11, 16, -1, -1, -1}};
const int N = (1 << 20) + 7;
const ll MIN = -1000000010ll;
ll Dp[N], n;
vector<int> E, A;
ll DP(int State) {
  if (Dp[State] != MIN) return Dp[State];
  Rep(i, 0, n - 1)
    if ((State >> i) & 1) {
      int to = State ^ (1 << i);
      Dp[State] = max(Dp[State], DP(to));
      Rep(j, 0, 5)
        if (~GO[i][j] && ((State >> GO[i][j]) & 1) &&
            ((State >> GO2[i][j]) & 1) == 0) {
          to = State ^ (1 << GO[i][j]) ^ (1 << GO2[i][j]) ^ (1 << i);
          Dp[State] = max(Dp[State], DP(to) + E[GO[i][j]]);
        }
    }
  return Dp[State];
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  n = 19;
  E.resize(n, 0);
  A.resize(n, 0);
  Rep(i, 0, n - 1) cin >> E[i];
  int T;
  cin >> T;
  Rep(i, 0, (1 << 20) - 1) Dp[i] = MIN;
  Dp[0] = 0;
  while (T--) {
    int State = 0;
    Rep(i, 0, n - 1) {
      char C;
      cin >> C;
      State |= (C == '#' ? 1 : 0) * (1 << i);
    }
    cout << DP(State) << '\n';
  }
  return 0;
}
