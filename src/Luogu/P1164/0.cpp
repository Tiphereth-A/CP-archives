#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
const int N = 100 + 5;
const int M = 1e4 + 5;
int n, m, a[N], f[N][M];
int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      f[i][j] =
        f[i - 1][j] + ((j == a[i]) ? 1 : ((j > a[i]) ? f[i - 1][j - a[i]] : 0));
  cout << f[n][m];
  return 0;
}
