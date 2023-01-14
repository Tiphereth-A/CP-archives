#include <bits/stdc++.h>
char a[6][62];
std::string s;
void f(char c, int y, int x) {
  a[3][y] = c;
  a[1][y] = a[2][y + 1] = a[3][y + 2] = a[4][y + 1] = a[5][y] = a[4][y - 1] =
    a[3][y - 2] = a[2][y - 1] = (x ? '#' : '*');
}
int main() {
  memset(a, '.', sizeof(a));
  std::cin >> s;
  int len = s.size();
  for (int i = 0; i < len; ++i) {
    if (i % 3 == 2) continue;
    f(s[i], 4 * i + 3, 1);
  }
  for (int i = 2; i < len; i += 3) { f(s[i], 4 * i + 3, 0); }
  for (int i = 1; i < 6; i++) {
    for (int j = 1; j < (len << 2) + 2; ++j) { std::cout << a[i][j]; }
    std::cout << std::endl;
  }
}
