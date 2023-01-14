#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
const int N = 1005;
int a[N][N];
i64 s[N][N];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, m, c;
  cin >> n >> m >> c;
  _for(i, 1, n)
    _for(j, 1, n) cin >> a[i][j];
  _for(i, 1, n)
    _for(j, 1, n)
      s[i][j] = a[i][j] + s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
  i64 ans = INT64_MIN;
  int x, y;
  _for(i, c, n)
    _for(j, c, n)
      if (i64 _ = s[i][j] - s[i - c][j] - s[i][j - c] + s[i - c][j - c];
          ans < _) {
        ans = _;
        x = i;
        y = j;
      }
  cout << x - c + 1 << " " << y - c + 1;
  return 0;
}
