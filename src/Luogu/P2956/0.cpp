#include <bits/stdc++.h>
bool t[255][255];
int main() {
  int x, y, n, s = 0;
  scanf("%d %d %d", &x, &y, &n);
  while (n--) {
    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    for (int i = a; i <= c; ++i)
      for (int j = b; j <= d; ++j) t[i][j] = 1;
  }
  for (int i = 1; i <= x; ++i)
    for (int j = 1; j <= y; ++j)
      if (t[i][j]) ++s;
  printf("%d\n", s);
  return 0;
}
