#include <bits/stdc++.h>
int main() {
  int a, b, c;
  std::cin >> a >> b >> c;
  if (b == 0) std::cout << 0;
  else std::cout << std::max(a - c / b - !!(c % b), 0);
}
