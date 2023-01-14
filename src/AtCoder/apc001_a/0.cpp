#include <iostream>
main() {
  int a, b;
  std::cin >> a >> b;
  if (a % b) std::cout << a << std::endl;
  else std::cout << "-1" << std::endl;
}
