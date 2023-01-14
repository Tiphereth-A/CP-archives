#include <bits/stdc++.h>
const int mod = 6662333;
long long n, a = 2, s = 1;
int main() {
  scanf("%lld", &n);
  n--;
  while (n) {
    if (n & 1) s = s * a % mod;
    a = a * a % mod;
    n >>= 1;
  }
  printf("%lld", s % mod);
  return 0;
}
