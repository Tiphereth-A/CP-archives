#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int N = 2000 + 5;
const i64 MOD = 1e9 + 7;
i64 c[N][N];
int w[N];
int main() {
  int n, m;
  for (int i = 0; i < N; ++i) {
    c[i][0] = 1;
    for (int j = 1; j <= i; ++j)
      c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % MOD;
  }
  cin >> n >> m;
  for (int i = 1; i <= m; ++i) cin >> w[i];
  i64 ans = 0;
  for (int i = 0; i < n; ++i) {
    i64 tmp = c[n][i];
    for (int j = 1; j <= m; ++j) tmp = tmp * c[w[j] + n - i - 1][w[j]] % MOD;
    ans = (ans + MOD + (i % 2 ? -1 : 1) * tmp % MOD) % MOD;
  }
  cout << ans << endl;
  return 0;
}
