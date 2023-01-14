#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
const int N = 500 + 5;
int f[N][N];
auto solve() -> void {
  int n, m;
  cin >> n >> m;
  memset(f, 0x3f, sizeof(f));
  _for(i, 1, n) f[i][i] = 0;
  _for(i, 1, m, x, y, z) {
    cin >> x >> y >> z;
    f[y][x] = f[x][y] = min(f[x][y], z);
  }
  _for(k, 1, n)
    _for(i, 1, n)
      _for(j, 1, n) f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
  int q;
  cin >> q;
  i64 ans = 0;
  _for(i, 1, q, x, prev = 1) {
    cin >> x;
    if (f[prev][x] == 0x3f3f3f3f) {
      cout << "-1";
      return;
    }
    ans += f[prev][x];
    prev = x;
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
