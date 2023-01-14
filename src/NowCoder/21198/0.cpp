#include <bits/stdc++.h>
std::string str, tmp;
int n;
int main() {
  std::cin >> n >> str;
  for (int i = 1; i <= n; ++i) {
    std::cin >> tmp;
    if (tmp == str) {
      std::cout << i;
      return 0;
    }
  }
  return 0;
}
