#include <bits/stdc++.h>
#define M 10005
#define _for(i, l, r) for (int i = (l); i <= (r); i++)
#define nos(a, b, n) \
  ((((a) < 1) || ((b) < 1) || ((a) > (n)) || ((b) > (n))) ? 0 : 1)
#define gi getint
#define gc getchar
using namespace std;
int g[M][M], n, m, k, x, y, ans;
int getint() {
  int t = 0;
  char c = gc();
  while (c < 48 || c > 57) c = gc();
  while (c >= 48 && c <= 57) {
    t = t * 10 + c - 48;
    c = gc();
  }
  return t;
}
int main() {
  n = gi(), m = gi(), k = gi();
  _for(i, 1, m) {
    x = gi();
    y = gi();
    _for(a, -2, 2)
      _for(b, -2, 2)
        if ((abs(a) + abs(b) <= 2) && nos(a + x, b + y, n)) ++g[a + x][b + y];
  }
  _for(i, 1, k) {
    x = gi();
    y = gi();
    _for(a, -2, 2)
      _for(b, -2, 2)
        if (nos(a + x, b + y, n)) ++g[a + x][b + y];
  }
  _for(x, 1, n)
    _for(y, 1, n) ans += (g[x][y] == 0);
  cout << ans;
  return 0;
}
