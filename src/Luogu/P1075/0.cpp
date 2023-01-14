#include <bits/stdc++.h>
int main() {
  int n;
  std::cin >> n;
  int s = ceil(sqrt(n)), a, b;
  for (int i = 2; i <= s; ++i) {
    if (n % i == 0) {
      a = i;
      b = n / i;
      break;
    }
  }
  std::cout << ((a > b) ? a : b);
  return 0;
}
