#include <cmath>
#include <cstdio>
i64 phi(i64 n) {
  i64 ans = n, sqn = sqrt(n + 0.5);
  for (i64 i = 2; i <= sqn; ++i) {
    if (n % i == 0) {
      (ans /= i) *= i - 1;
      while (n % i == 0) n /= i;
    }
  }
  if (n > 1) (ans /= n) *= n - 1;
  return ans;
}
int main() {
  i64 n;
  while ((n = 0, scanf("%lld", &n)) && n) {
    i64 ans = n + phi(n);
    for (int i = 2; i <= sqrt(n + 0.5); ++i) {
      if (n % i == 0) ans += i * phi(n / i) + (n / i != i) * n / i * phi(i);
    }
    printf("%lld\n", ans);
  }
  return 0;
}
