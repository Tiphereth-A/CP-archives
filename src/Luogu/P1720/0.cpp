#include <bits/stdc++.h>
long long a, b = 1, c = 1;
int main() {
  int n;
  std::cin >> n;
  for (int i = 1; i <= n; ++i) {
    a = b;
    b = c;
    c = a + b;
  }
  std::cout << a << ".00";
  return 0;
}
