#include <bits/stdc++.h>
int n, ans = 1, num[4] = {6, 8, 4, 2};
int main() {
  scanf("%d", &n);
  while (n > 0) {
    int t = n % 10;
    for (int i = 1; i <= t; ++i)
      if (i != 5) ans = ans * i % 10;
    n = n / 5;
    ans = ans * num[n % 4] % 10;
  }
  printf("%d", ans);
  return 0;
}
