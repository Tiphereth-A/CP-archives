#include <bits/stdc++.h>
#define _r (i + p[i])
#define _l (i - p[i])
const int N = 1e5 + 5, M = 2e5 + 15;
char a[N], s[M] = "#";
int len, p[M], l[M], r[M];
int max(int x, int y) {
  int m = (x - y) >> 31;
  return (x & ~m) | (y & m);
}
int min(int x, int y) {
  int m = (y - x) >> 31;
  return (x & ~m) | (y & m);
}
void read() {
  scanf("%s", a);
  len = strlen(a);
  for (int i = 0; i < len; ++i) {
    s[i << 1 | 1] = '#';
    s[(i + 1) << 1] = a[i];
  }
  s[len = len << 1 | 1] = '#';
}
void manacher() {
  int rMax = 0, mid = 0;
  for (int i = 1; i <= len; ++i) {
    p[i] = (i < rMax) ? min(p[(mid << 1) - i], rMax - i) : 1;
    while (1 <= _l && _r <= len && s[_l] == s[_r]) ++p[i];
    if (rMax < _r) {
      rMax = _r;
      mid = i;
    }
  }
}
int main() {
  read();
  manacher();
  int now = 0, tmp;
  ++len;
  for (int i = 0; i < len; ++i) {
    tmp = _r;
    while (now < tmp) l[now++] = i;
  }
  now = len;
  for (int i = len - 1; ~i; --i) {
    tmp = _l;
    while (now > tmp) r[now--] = i;
  }
  int ans = 0;
  for (int i = 0; i < len; ++i) ans = max(ans, r[i] - l[i]);
  printf("%d", ans);
}
