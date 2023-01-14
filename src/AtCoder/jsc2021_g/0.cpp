#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
#define _for(i, l, r) for (auto i = (l); i <= (r); ++i)
#define _run_exit(expressions) _run_return(expressions, 0)
#define _run_return(expressions, val) return (expressions), val
#define _run_break(expressions) \
  {                             \
    expressions;                \
    break;                      \
  }
const int N = 3e2 + 5, MOD = 1e9 + 7;
int fa[N];
int find(int x) { return x == fa[x] ? fa[x] : fa[x] = find(fa[x]); }
int a[N][N];
int cnt;
i64 lap[N][N];
int id[N];
vector<int> vals[N];
i64 inv(i64 a, i64 mod = MOD) {
  i64 res = 1, b = mod - 2;
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
int main() {
  int n;
  cin >> n;
  _for(i, 1, n)
    _for(j, 1, n) cin >> a[i][j];
  _for(i, 1, n) fa[i] = i;
  _for(i, 1, n)
    _for(j, i + 1, n)
      if (a[i][j] == 1) {
        int fi = find(i), fj = find(j);
        if (fi == fj) _run_exit(cout << 0);
        fa[fi] = fj;
      }
  _for(i, 1, n) {
    bool f = 1;
    _for(j, 1, n)
      if (!id[j]) {
        f = 0;
        int nowf = find(j);
        _for(k, j, n)
          if (find(k) == nowf) {
            id[k] = i;
            vals[i].push_back(k);
          }
        break;
      }
    if (f) _run_break(cnt = i - 1);
  }
  if (!cnt) cnt = n;
  if (cnt == 1) _run_exit(cout << 1);
  _for(i, 1, cnt)
    _for(j, i + 1, cnt) {
      for (int x : vals[i])
        for (int y : vals[j])
          if (a[x][y] == -1) --lap[i][j];
      lap[i][i] -= lap[j][i] = lap[i][j];
      lap[j][j] -= lap[j][i];
    }
  --cnt;
  i64 ans = 1;
  _for(i, 1, cnt) {
    if (!lap[i][i]) {
      _for(j, i + 1, cnt)
        if (lap[j][i]) {
          _for(k, 1, cnt) swap(lap[i][k], lap[j][k]);
          _run_break(ans *= -1);
        }
      if (!lap[i][i]) _run_exit(cout << 0);
    }
    (((ans *= lap[i][i]) %= MOD) += MOD) %= MOD;
    i64 now_inv =
      inv(lap[i][i] < 0 ? (lap[i][i] % MOD + MOD) % MOD : lap[i][i]);
    _for(j, i, cnt) (((lap[i][j] *= now_inv) %= MOD) += MOD) %= MOD;
    _for(j, i + 1, cnt) {
      _for(k, i + 1, cnt)
        (((lap[j][k] -= lap[i][k] * lap[j][i] % MOD) %= MOD) += MOD) %= MOD;
      lap[j][i] = 0;
    }
  }
  cout << ans;
FINISHED:
  return 0;
}
