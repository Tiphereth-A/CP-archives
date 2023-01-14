#include <bits/stdc++.h>
#define _l(a) ((a) - r[a])
#define _r(a) ((a) + r[a])
const int N = 11000005;
char s[N << 1 | 1], a[N];
int len, r[N << 1 | 1];
int min(int x, int y) {
  int m = (y - x) >> 31;
  return (x & ~m) | (y & m);
}
int max(int x, int y) {
  int m = (x - y) >> 31;
  return (x & ~m) | (y & m);
}
int main() {
  scanf("%s", a);
  len = strlen(a);
  s[0] = s[1] = '#';
  for (int i = 1; i <= len; ++i) {
    s[i << 1] = a[i - 1];
    s[i << 1 | 1] = '#';
  }
  len = len << 1 | 1;
  int rMax = 0, mid = 0;
  for (int i = 1; i <= len; ++i) {
    r[i] = (i < rMax) ? min(r[(mid << 1) - i], rMax - i) : 1;
    while (1 <= _l(i) && _r(i) <= len && s[_l(i)] == s[_r(i)]) ++r[i];
    if (_r(i) > rMax) {
      rMax = _r(i);
      mid = i;
    }
  }
  int lMax = 0;
  for (int i = 1; i <= len; ++i) lMax = max(lMax, r[i] - 1);
  printf("%d\n", lMax);
  return 0;
}
