#include <cstdio>
u64 a[35] = {0, 1}, b[35] = {0, 1};
u64 gcd(u64 a, u64 b) { return !b ? a : gcd(b, a % b); }
int get_len(u64 n) {
  int ans = 0;
  do ++ans;
  while (n /= 10);
  return ans;
}
int main() {
  for (int i = 2; i <= 33; ++i) {
    a[i] = a[i - 1] * i + b[i - 1];
    b[i] = b[i - 1] * i;
    u64 tmp = gcd(a[i], b[i]);
    a[i] /= tmp;
    b[i] /= tmp;
  }
  for (int i = 2; i <= 33; ++i) {
    a[i] *= i;
    u64 tmp = gcd(a[i], b[i]);
    a[i] /= tmp;
    b[i] /= tmp;
  }
  int n;
  while (~scanf("%d", &n)) {
    u64 A = a[n], B = b[n];
    if (B == 1) printf("%llu\n", A);
    else {
      u64 d = A / B;
      A -= d * B;
      int ld = get_len(d), lb = get_len(B);
      for (int i = 0; i <= ld; ++i) putchar(' ');
      printf("%llu\n%llu ", A, d);
      for (int i = 1; i <= lb; ++i) putchar('-');
      puts("");
      for (int i = 0; i <= ld; ++i) putchar(' ');
      printf("%llu\n", B);
    }
  }
  return 0;
}
