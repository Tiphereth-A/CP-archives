#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
long long qpow(long long a, long long b, long long mod) {
  long long res = 1;
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
long long gcd(long long a, long long b) { return b == 0 ? a : gcd(b, a % b); }
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
  long long a, b;
  long long kase = 0;
  while ((a = b = 0, scanf("%lld/%lld", &a, &b)) && (a || b)) {
    long long g = gcd(a, b);
    a /= g;
    b /= g;
    long long _ = b, ans1 = 1;
    while (!(_ & 1)) {
      _ >>= 1;
      ++ans1;
    }
    b /= (1 << (ans1 - 1));
    long long ans2 = 0;
    if (b > 1) {
      ans2 = _ = phi(b);
      for (long long i = 2; i <= sqrt(_ + 0.5); ++i) {
        if (_ % i == 0) {
          if (qpow(2ll, i, b) == 1ll) {
            ans2 = i;
            break;
          }
          if (qpow(2ll, _ / i, b) == 1ll) ans2 = _ / i;
        }
      }
    }
    cout << "Case #" << ++kase << ": " << ans1 << "," << ans2 << endl;
  }
  return 0;
}
