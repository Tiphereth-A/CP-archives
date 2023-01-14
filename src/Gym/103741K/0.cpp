#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
const uint32_t N = 500;
bool maps[N][N];
auto solve() -> void {
  int n;
  cin >> n;
  _for(i, 1, n, x, y) {
    cin >> x >> y;
    maps[x][y] = 1;
  }
  i64 ans = 0;
  _for(i, -500, 500) {
    i64 cnt = 0;
    for (int j = max(1, 1 - i), k = max(1, i + 1); j <= 500 && k <= 500;
         ++j, ++k) {
      if (!maps[j][k]) {
        ans += cnt * (cnt + 1);
        cnt = 0;
        continue;
      }
      ++cnt;
    }
    ans += cnt * (cnt + 1);
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
