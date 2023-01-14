#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
int n;
std::set<std::string> s;
std::string str;
int main() {
  std::ios::sync_with_stdio(false);
  std::cin >> n;
  _for(i, 1, n) {
    std::cin >> str;
    std::string a = "";
    for (auto j : str) {
      if (j == '/') s.insert(a);
      a += j;
    }
    s.insert(a);
    std::cout << s.size() - 1 << std::endl;
  }
  return 0;
}
