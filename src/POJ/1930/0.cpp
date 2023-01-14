#include <cmath>
#include <cstdio>
#include <cstring>
i64 gcd(i64 a, i64 b) { return b == 0 ? a : gcd(b, a % b); }
char s[20];
int main() {
  while (scanf("%s", s), (strlen(s) > 1)) {
    i64 n = 0, len = 0;
    for (len = 2; s[len] != '.'; ++len) (n *= 10) += s[len] - '0';
    i64 mol = 0x3f3f3f3f3f3f3f3f, den = 0;
    for (int i = 2; i < len; ++i) {
      i64 _ = 0;
      for (int j = 2; j <= i - 1; ++j) (_ *= 10) += s[j] - '0';
      i64 x = n - _,
          y = pow(10.0, (double)(i - 2)) * (pow(10.0, (double)(len - i)) - 1);
      i64 g = gcd(x, y);
      if (y / g < mol) {
        den = x / g;
        mol = y / g;
      }
    }
    printf("%lld/%lld\n", den, mol);
  }
  return 0;
}
