#include <bits/stdc++.h>
#define M 10005
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define _rfor(i, r, l) for (int i = (r); i >= (l); --i)
#define gi getint
#define gc getchar
using namespace std;
int f[M], n, V, v[105], w[105];
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
  n = gi();
  V = gi();
  _for(i, 1, n) v[i] = gi();
  f[0] = 1;
  _for(i, 1, n)
    _rfor(j, V, v[i]) f[j] += f[j - v[i]];
  cout << f[V];
  return 0;
}
