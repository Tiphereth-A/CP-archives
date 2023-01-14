#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
ll f[21][21] = {1};
bool mark[21][21];
const int d[2][9] = {{0, -2, -1, 1, 2, 2, 1, -1, -2},
                     {0, 1, 2, 2, 1, -1, -2, -2, -1}};
int main() {
  int xb, yb, xh, yh;
  cin >> xb >> yb >> xh >> yh;
  for (int i = 0; i < 9; ++i)
    if (xh + d[0][i] >= 0 && xh + d[0][i] <= xb && yh + d[1][i] >= 0 &&
        yh + d[1][i] <= yb)
      mark[xh + d[0][i]][yh + d[1][i]] = 1;
  for (int i = 0; i <= xb; ++i)
    for (int j = 0; j <= yb; ++j) {
      if (i) f[i][j] += f[i - 1][j];
      if (j) f[i][j] += f[i][j - 1];
      f[i][j] *= !mark[i][j];
    }
  cout << f[xb][yb];
  return 0;
}
