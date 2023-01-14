#include <bits/stdc++.h>
int t1, t2;
int main() {
  int h, m, s;
  scanf("%d:%d:%d", &h, &m, &s);
  t1 = h * 3600 + m * 60 + s;
  scanf("%d:%d:%d", &h, &m, &s);
  t2 = h * 3600 + m * 60 + s;
  if (t1 > t2) t1 -= t2;
  else t1 = t2 - t1;
  s = t1 % 60;
  t1 /= 60;
  m = t1 % 60;
  h = t1 / 60;
  printf("%0.2d:%0.2d:%0.2d", h, m, s);
  return 0;
}
