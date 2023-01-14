#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define mem(a) memset(a, 0, sizeof(a))
#define MOD(x, p) ((x) % (p))
typedef long long ll;
struct mat {
  ll n[3][3];
  mat() { mem(n); }
} ans, mul;
ll m, n, g;
ll qmul(ll a, ll b) {
  ll tmp = 0;
  for (; b; b >>= 1) {
    if (b & 1) tmp = MOD(tmp + a, m);
    a = MOD(a << 1, m);
  }
  return tmp;
}
mat Mul(mat a, mat b) {
  mat tmp;
  _for(i, 1, 2)
    _for(j, 1, 2)
      _for(k, 1, 2) {
        tmp.n[i][j] = MOD(tmp.n[i][j] + MOD(qmul(a.n[i][k], b.n[k][j]), m), m);
        if (tmp.n[i][j] < 0) tmp.n[i][j] += m;
      }
  return tmp;
}
mat qpow() {
  mat tmp;
  tmp.n[1][1] = tmp.n[2][2] = 1;
  for (; n; n >>= 1) {
    if (n & 1) tmp = Mul(tmp, mul);
    mul = Mul(mul, mul);
  }
  return tmp;
}
int main() {
  scanf("%lld%lld%lld%lld%lld%lld",
        &m,
        &mul.n[1][1],
        &mul.n[2][1],
        &ans.n[1][1],
        &n,
        &g);
  mul.n[2][2] = ans.n[1][2] = 1;
  mul = qpow();
  ans = Mul(ans, mul);
  printf("%lld", MOD(ans.n[1][1], g));
  return 0;
}
