#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define _rfor(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
int n;
char c[1024][2048];
int main() {
  ios::sync_with_stdio(false);
  cin >> n;
  int l = 4, flo = 1;
  _for(i, 0, 1023)
    _for(j, 0, 2047) c[i][j] = '\x20';
  c[0][0] = c[1][1] = '/';
  c[0][1] = c[0][2] = '_';
  c[0][3] = c[1][2] = '\\';
  while (flo < n) {
    int h = l >> 1;
    _for(i, 0, h - 1)
      _for(j, 0, l - 1) c[i + h][j + h] = c[i][j + l] = c[i][j];
    l <<= 1;
    flo++;
  }
  _rfor(i, (l >> 1) - 1, 0) {
    _for(j, 0, l - 1) cout << c[i][j];
    cout << endl;
  }
  return 0;
}
