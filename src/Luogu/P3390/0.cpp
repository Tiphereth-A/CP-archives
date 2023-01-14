#include <bits/stdc++.h>
#define MOD 1000000007
typedef long long ll;
#define _for(i, l, r) for (int(i) = (l); (i) <= (r); i++)
using namespace std;
struct Mtx {
  ll m[101][101];
} a, b;
ll n, p;
Mtx Mul(const Mtx &x, const Mtx &y) {
  Mtx c;
  memset(c.m, 0, sizeof(c.m));
  _for(i, 1, n)
    _for(j, 1, n)
      _for(k, 1, n) {
        c.m[i][j] = c.m[i][j] % MOD + x.m[i][k] * y.m[k][j] % MOD;
      }
  return c;
}
Mtx pow(Mtx x, ll y) {
  Mtx ans = b;
  while (y) {
    if (y & 1) ans = Mul(ans, x);
    x = Mul(x, x);
    y >>= 1;
  }
  return ans;
}
int main() {
  ios::sync_with_stdio(false);
  cin >> n >> p;
  _for(i, 1, n)
    _for(j, 1, n) cin >> a.m[i][j];
  _for(i, 1, n) b.m[i][i] = 1;
  Mtx ans = pow(a, p);
  _for(i, 1, n) {
    _for(j, 1, n) cout << ans.m[i][j] % MOD << " ";
    cout << endl;
  }
  return 0;
}
