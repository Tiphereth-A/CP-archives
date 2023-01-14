#include <bits/stdc++.h>
int a[45][45];
using namespace std;
int main() {
  int n;
  cin >> n;
  int x = 1, y = (n + 1) >> 1;
  a[x][y] = 1;
  for (int k = 2; k <= n * n; k++) {
    if (x == 1 && y != n) {
      x = n;
      y++;
    } else if (x != 1 && y == n) {
      x--;
      y = 1;
    } else if (x == 1 && y == n) x++;
    else if (!a[x - 1][y + 1]) {
      x--;
      y++;
    } else x++;
    a[x][y] = k;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) printf("%d ", a[i][j]);
    printf("\n");
  }
  return 0;
}
