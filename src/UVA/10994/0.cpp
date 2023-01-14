#include <cstdio>
i64 s(i64 n) {
  i64 ans = 0;
  while (n) {
    ans += (n % 10) * ((n % 10) + 1) / 2 + (n / 10) * 45;
    n /= 10;
  }
  return ans;
}
int main() {
  i64 a, b;
  while (~scanf("%lld%lld", &a, &b), (~a || ~b))
    printf("%lld\n", s(b) - s(a - 1));
  return 0;
}
