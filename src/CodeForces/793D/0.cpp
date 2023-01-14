#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _set_inf(a) memset(a, 0x3f, sizeof(a))
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
const uint32_t OFFSET = 5;
const uint32_t N = 80 + OFFSET;
const int INF = 0x3f3f3f3f;
int f[2][N][N];
int g[N][N];
void solve() {
  _set_inf(g);
  int n, k, m;
  cin >> n >> k >> m;
  _for(i, 1, m, x, y, w) {
    cin >> x >> y >> w;
    chkmin(g[x][y], w);
  }
  _set_inf(f[0]);
  _for(i, 1, n) f[0][i][0] = f[0][i][n + 1] = 0;
  _for(cnt, 1, k, now = 0) {
    now ^= 1;
    _set_inf(f[now]);
    _for(l, 0, n + 1, _)
      _for(r, l, n + 1)
        _for(to, l + 1, r - 1) {
          _ = min(f[now ^ 1][l][r] + g[l][to], f[now ^ 1][r][l] + g[r][to]);
          chkmin(f[now][to][r], _);
          chkmin(f[now][to][l], _);
        }
  }
  int ans = INF;
  _for(l, 0, n + 1)
    _for(r, 0, n + 1) chkmin(ans, min(f[~k & 1][l][r], f[~k & 1][r][l]));
  cout << (ans == INF ? -1 : ans);
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
