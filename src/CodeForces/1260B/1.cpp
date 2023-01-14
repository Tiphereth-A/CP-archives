#include <bits/stdc++.h>
int main() {
  int t;
  std::cin >> t;
  while (t--) {
    unsigned a, b;
    std::cin >> a >> b;
    std::cout << (((a + b) % 3 || std::max(a, b) > 2 * std::min(a, b)) ? "NO" :
                                                                         "YES")
              << std::endl;
  }
  return 0;
}
