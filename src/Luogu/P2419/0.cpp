#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define for_(i, l, r, vars...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vars; i <= i##end; ++i)
bool f[101][101];
int main() {
  int n, m;
  cin >> n >> m;
  for_(i, 1, m, a, b) {
    cin >> a >> b;
    f[a][b] = 1;
  }
  for_(k, 1, n)
    for_(i, 1, n)
      for_(j, 1, n) f[i][j] |= f[i][k] & f[k][j];
  i64 ans = 0;
  for_(i, 1, n, _) {
    _ = 1;
    for_(j, 1, n)
      if (i != j) _ &= (f[i][j] | f[j][i]);
    ans += _;
  }
  cout << ans;
}
