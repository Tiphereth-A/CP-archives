#include <bits/stdc++.h>
using std::cin;
using std::cout;
bool vis[10][10];
std::string str;
int k, cnt[10];
std::ostream &operator<<(std::ostream &os, __uint128_t num) {
  std::string str(" ");
  while (num) {
    str.push_back(num % 10 + '0');
    num /= 10;
  }
  for (auto i = str.end(); i != str.begin();) os << *--i;
  return os;
}
int main() {
  cin >> str >> k;
  for (int i = 1, x, y; i <= k; ++i) {
    cin >> x >> y;
    vis[x][y] = true;
  }
  for (int k = 1; k < 10; ++k)
    for (int i = 0; i < 10; ++i)
      for (int j = 1; j < 10; ++j) { vis[i][j] |= vis[i][k] && vis[k][j]; }
  __uint128_t ans = 1;
  for (int i = 0; i < 10; ++i) {
    vis[i][i] = true;
    for (int j = 0; j < 10; ++j) cnt[i] += vis[i][j];
  }
  for (auto c : str) ans *= cnt[c - '0'];
  cout << ans;
  return 0;
}
