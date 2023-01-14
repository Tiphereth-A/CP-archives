#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r) for (int i = (l); i < (r); ++i)
const int K = 21;
bool g[K][K];
i64 f[K][1 << K];
int main() {
  _for(i, 0, K)
    _for(j, i + 1, K) g[i][j] = g[j][i] = (__gcd(i + 1, j + 1) == 1);
  f[0][1] = 1;
  _for(i, 0, 1 << K)
    _for(j, 0, K)
      if ((i >> j) & 1)
        _for(k, 0, K)
          if (g[j][k] && ((i >> k) & 1)) f[j][i] += f[k][i ^ (1 << j)];
  i64 ans = 0;
  _for(i, 1, K) ans += f[i][(1 << K) - 1];
  cout << ans;
}
