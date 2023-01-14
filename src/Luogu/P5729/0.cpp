#include <bits/stdc++.h>
using namespace std;
const int N = 25;
bool a[N][N][N];
int main() {
  int w, x, h, q;
  cin >> w >> x >> h >> q;
  for (int i = 1, x1, x2, y1, y2, z1, z2; i <= q; ++i) {
    cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
    for (int i = x1; i <= x2; ++i)
      for (int j = y1; j <= y2; ++j)
        for (int k = z1; k <= z2; ++k) a[i][j][k] = 1;
  }
  int cnt = 0;
  for (int i = 1; i <= w; ++i)
    for (int j = 1; j <= x; ++j)
      for (int k = 1; k <= h; ++k) cnt += !a[i][j][k];
  cout << cnt;
  return 0;
}
