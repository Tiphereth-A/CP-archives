#include <bits/stdc++.h>
#define N 5
#define M 2
typedef long long ll;
struct matrix {
  ll m[N][N];
} a, b;
ll mod;
matrix mul(const matrix &m, const matrix &n) {
  matrix t;
  memset(t.m, 0, sizeof(t.m));
  for (int i = 1; i <= M; ++i)
    for (int j = 1; j <= M; ++j)
      for (int k = 1; k <= M; ++k)
        t.m[i][j] = (t.m[i][j] + (m.m[i][k] * n.m[k][j]) % mod) % mod;
  return t;
}
void pow(ll k) {
  while (k) {
    if (k & 1) b = mul(b, a);
    a = mul(a, a);
    k >>= 1;
  }
}
int main() {
  ll p, q, a1, a2, n;
  scanf("%lld%lld%lld%lld%lld%lld", &p, &q, &a1, &a2, &n, &mod);
  b.m[1][1] = a2;
  b.m[1][2] = a1;
  a.m[1][2] = 1;
  a.m[1][1] = p;
  a.m[2][1] = q;
  if (n == 1) printf("%lld\n", a1 % mod);
  else if (n == 2) printf("%lld\n", a2 % mod);
  else {
    pow(n - 2);
    printf("%lld\n", b.m[1][1] % mod);
  }
  return 0;
}
