#include <bits/stdc++.h>
int main() {
  int f, n, t = 0, num = 0;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &f);
    if (!f) ++t;
    else ++num;
  }
  if (!t) {
    printf("-1");
    return 0;
  }
  if (num < 9) {
    printf("0");
    return 0;
  }
  num -= (num % 9);
  for (int i = 1; i <= num; ++i) putchar('5');
  for (int i = 1; i <= t; ++i) putchar('0');
  return 0;
}
