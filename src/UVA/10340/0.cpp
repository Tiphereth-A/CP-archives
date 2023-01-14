#include <iostream>
#include <queue>
#include <string>
int main() {
  std::string s, t;
  while (std::cin >> s >> t) {
    std::queue<char> qs;
    for (const char &i : s) qs.push(i);
    for (const char &i : t)
      if (i == qs.front()) qs.pop();
    std::cout << (qs.empty() ? "Yes" : "No") << std::endl;
  }
}
