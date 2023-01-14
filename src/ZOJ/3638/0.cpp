#include <cstdio>
#include <cstring>
const i64 mod = 100000007;
i64 qpow(i64 a, i64 b) {
  i64 res = 1;
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
i64 lucas(i64 a, i64 b) {
  if (a < b || a < 0 || b < 0) return 0;
  i64 res = 1, _ = 1;
  for (int i = 0; i < b; i++) {
    res = res * (a - i) % mod;
    _ = _ * (i + 1) % mod;
  }
  return res * qpow(_, mod - 2) % mod;
}
char op[505], line[5005];
int limit[505];
int main() {
  int m, n;
  while (~scanf("%d%d", &n, &m) && (m != 1 || n)) {
    int k = 0, _;
    fgets(line, sizeof(line), stdin);
    while (fgets(line, sizeof(line), stdin) && line[0] != '\n' &&
           line[1] != '\n') {
      sscanf(line, "%*s%s%*s%d\n", op, &_);
      if (op[0] == 'g') m -= _ + 1;
      else limit[++k] = _;
    }
    if (m < 0) {
      puts("0");
      continue;
    }
    i64 ans = 0;
    for (int i = 0; i < (1 << k); ++i) {
      int _ = 0, now = 0;
      for (int j = 1; j <= k; ++j)
        if (i & (1 << j - 1)) {
          ++_;
          now += limit[j];
        }
      ans += (_ & 1 ? -1 : 1) * lucas(n + m - 1 - now, n - 1);
    }
    printf("%lld\n", (ans % mod + mod) % mod);
  }
}
