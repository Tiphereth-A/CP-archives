#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define _rfor(i, r, l) for (int i = (r); i >= (l); --i)
#define M 1005
int n;
char tmp, llt[M][M];
bool m[M][M];
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  _for(i, 1, n)
    _for(j, 1, n) {
      cin >> tmp;
      if (tmp == 'O') m[i][j] = true;
    }
  _for(i, 1, n)
    _for(j, 1, n) cin >> llt[i][j];
  _for(i, 1, n)
    _for(j, 1, n)
      if (m[i][j]) cout << llt[i][j];
  _for(i, 1, n)
    _rfor(j, n, 1)
      if (m[j][i]) cout << llt[i][n - j + 1];
  _rfor(i, n, 1)
    _rfor(j, n, 1)
      if (m[i][j]) cout << llt[n - i + 1][n - j + 1];
  _rfor(i, n, 1)
    _for(j, 1, n)
      if (m[j][i]) cout << llt[n - i + 1][j];
  return 0;
}
