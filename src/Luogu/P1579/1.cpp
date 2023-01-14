#include <bits/stdc++.h>
bool prime(int n) {
  int i = 2;
  while (i <= sqrt(n))
    if (!(n % i++)) return false;
  return true;
}
int main() {
  int n;
  std::cin >> n;
  for (int i = 2; i <= sqrt(n); ++i) {
    for (int j = 2; j <= sqrt(n - i); ++j) {
      int k = n - i - j;
      if (prime(i) && prime(j) && prime(k)) {
        std::cout << i << ' ' << j << ' ' << k;
        return 0;
      }
    }
  }
  return 0;
}
