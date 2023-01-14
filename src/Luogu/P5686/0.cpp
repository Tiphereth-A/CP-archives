#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (auto i = (l); i <= (r); ++i)
const int N = 5e5 + 5;
const i64 MOD = 1e9 + 7;
i64 a[N], b;
i64 sa[N], sb[N], ssb[N];
int main() {
  i64 n;
  scanf("%lld", &n);
  i64 ssa = 0;
  _for(i, 1ll, n) {
    scanf("%lld", a + i);
    sa[i] = (sa[i - 1] + a[i]) % MOD;
    (ssa += 1ll * i * a[i]) %= MOD;
  }
  _for(i, 1ll, n) {
    scanf("%lld", &b);
    sb[i] = (sb[i - 1] + b) % MOD;
    ssb[i] = (ssb[i - 1] + b * i) % MOD;
  }
  i64 ans = 0;
  _for(i, 1ll, n) {
    ans +=
      a[i] * (ssb[i] + (i * (((sb[n] - sb[i]) % MOD + MOD) % MOD)) % MOD) % MOD;
    ans %= MOD;
  }
  (ans *= n + 1) %= MOD;
  (ans -= ssa * ssb[n] % MOD) %= MOD;
  printf("%lld", (ans + MOD) % MOD);
  return 0;
}
