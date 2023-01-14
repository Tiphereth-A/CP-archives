#include <bits/stdc++.h>
using std::cin;
using std::cout;
bool f[105];
int main() {
  int n, m;
  cin >> n >> m;
  for (int i = 1, j = 1, cnt = 1; cnt <= n; ++i, ++j) {
    if (i == n + 1) i = 1;
    if (f[i]) j--;
    if (j == m) {
      f[i] = 1;
      cout << i << ' ';
      j = 0;
      cnt++;
    }
  }
  return 0;
}
