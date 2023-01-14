#include <bits/stdc++.h>
using std::cin;
using std::cout;
int f[45][45];
int main() {
  int n;
  cin >> n;
  int x = 0, y = n >> 1;
  f[x][y] = 1;
  for (int i = 2; i <= n * n; ++i) {
    if (x == 0 && y != n - 1) f[x = n - 1][++y] = i;
    else if (y == n - 1 && x) f[--x][y = 0] = i;
    else if (x == 0 && y == n - 1) f[++x][y] = i;
    else if (x && y != n - 1) f[x - 1][y + 1] ? f[++x][y] = i : f[--x][++y] = i;
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) { cout << f[i][j] << ' '; }
    cout << std::endl;
  }
  return 0;
}
