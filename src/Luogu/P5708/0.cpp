#include <bits/stdc++.h>
int main() {
  double a, b, c;
  std::cin >> a >> b >> c;
  double p = (a + b + c) / 2;
  std::cout << std::fixed << std::setprecision(1)
            << sqrt(p * (p - a) * (p - b) * (p - c));
}
