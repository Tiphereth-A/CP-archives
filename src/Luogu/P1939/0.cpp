#include <bits/stdc++.h>
#define N 5
typedef long long ll;
const ll MOD = 1000000007LL;
struct matrix {
  ll m[N][N];
} a, b;
matrix mul(const matrix &m, const matrix &n) {
  matrix t;
  memset(t.m, 0, sizeof(t.m));
  for (int i = 1; i <= 3; ++i)
    for (int j = 1; j <= 3; ++j)
      for (int k = 1; k <= 3; ++k)
        t.m[i][j] = (t.m[i][j] + (m.m[i][k] * n.m[k][j]) % MOD) % MOD;
  return t;
}
void pow(long long k) {
  while (k) {
    if (k & 1) b = mul(b, a);
    a = mul(a, a);
    k >>= 1;
  }
}
int main() {
  ll m, t;
  scanf("%lld", &t);
  while (t--) {
    scanf("%lld", &m);
    memset(b.m, 0, sizeof(b.m));
    memset(a.m, 0, sizeof(a.m));
    for (int i = 1; i <= 3; ++i) b.m[i][i] = 1;
    a.m[3][3] = a.m[1][3] = a.m[2][1] = a.m[3][2] = 1;
    if (m <= 3) printf("1\n");
    else {
      pow(m - 3);
      printf("%lld\n", (b.m[3][3] + b.m[1][3] + b.m[2][3]) % MOD);
    }
  }
  return 0;
}
