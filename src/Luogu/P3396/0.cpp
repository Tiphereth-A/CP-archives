#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
const int N = 1.5e5 + 5, M = sqrt(N) + 5;
i64 a[N];
i64 block[M][M];
int main() {
  int n, m;
  cin >> n >> m;
  _for(i, 1, n) cin >> a[i];
  int block_len = sqrt(n);
  _for(i, 1, n)
    _for(p, 1, block_len) block[p][i % p] += a[i];
  char op;
  i64 x, y;
  _for(i, 1, m) {
    cin >> op >> x >> y;
    if (op == 'A') {
      if (x <= block_len) {
        cout << block[x][y] << '\n';
        continue;
      }
      i64 ans = 0;
      for (int i = y; i <= n; i += x) ans += a[i];
      cout << ans << '\n';
      continue;
    }
    _for(p, 1, block_len) block[p][x % p] -= a[x] - y;
    a[x] = y;
  }
  return 0;
}
