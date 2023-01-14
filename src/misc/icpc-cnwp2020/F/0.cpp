#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5, MOD = 1e9 + 7;
int plu(int u, int v) { return (u + v) % MOD; }
int dec(int u, int v) { return (u - v + MOD) % MOD; }
int mul(int u, int v) { return (int)(1LL * u * v % MOD); }
int n, a[N], cnt, b[N];
void dobf() {
  int _b = (cnt & 1) ? -1 : 1;
  --n;
  cnt = (cnt + n) & 1;
  for (int i = 1; i <= n; ++i) {
    if (_b == 1) b[i] = plu(a[i], a[i + 1]);
    else b[i] = dec(a[i], a[i + 1]);
    _b = -_b;
  }
  for (int i = 1; i <= n; ++i) a[i] = b[i];
}
int sum(int u) { return ((1LL * u * (u + 1) / 2) & 1) ^ 1; }
int fac[N], inv[N];
int C(int u, int v) { return mul(fac[u], mul(inv[v], inv[u - v])); }
void sip() {
  --n;
  cnt = (cnt + sum(n)) & 1;
  int c[5] = {0, 0, 0};
  int tim = (n - 1) >> 1;
  for (int i = 0, xs, ia, ib; i <= tim; ++i) {
    xs = C(tim, i);
    ia = (i << 1 | 1);
    ib = ((i + 1) << 1);
    c[1] = plu(c[1], mul(xs, a[ia]));
    c[2] = plu(c[2], mul(xs, a[ib]));
  }
  n = 2;
  a[1] = c[1];
  a[2] = c[2];
}
int qpow(int u, int v) {
  int tmp = 1;
  while (v > 0) {
    if (v & 1) tmp = mul(tmp, u);
    u = mul(u, u);
    v >>= 1;
  }
  return tmp;
}
void init() {
  fac[0] = 1;
  int lmt = 2e5;
  for (int i = 1; i <= lmt; ++i) fac[i] = mul(fac[i - 1], i);
  inv[lmt] = qpow(fac[lmt], MOD - 2);
  for (int i = lmt - 1; ~i; i--) inv[i] = mul(inv[i + 1], i + 1);
}
int main() {
  init();
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
  if (n == 1) {
    printf("%d\n", a[1]);
    return 0;
  }
  if (n & 1) dobf();
  sip();
  dobf();
  printf("%d\n", a[1]);
  return 0;
}
