#include <bits/stdc++.h>
int a[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int main() {
  int x, y;
  scanf("%d%d", &x, &y);
  if ((!(x % 400) || (x % 100 && !(x % 4))) && y == 2) printf("29");
  else printf("%d", a[y]);
}
