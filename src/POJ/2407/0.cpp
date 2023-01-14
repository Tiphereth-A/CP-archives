#include <cmath>
#include <cstdio>
long long phi(long long n) {
  long long ans = n, sqn = sqrt(n + 0.5);
  for (long long i = 2; i <= sqn; ++i) {
    if (n % i == 0) {
      (ans /= i) *= i - 1;
      while (n % i == 0) n /= i;
    }
  }
  if (n > 1) (ans /= n) *= n - 1;
  return ans;
}
int main() {
  long long a;
  while ((a = 0, scanf("%lld", &a)) && a) printf("%lld\n", phi(a));
  return 0;
}
