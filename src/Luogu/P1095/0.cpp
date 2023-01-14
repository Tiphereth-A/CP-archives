#include <bits/stdc++.h>
int f[300010], m, s, t;
int main() {
  scanf("%d%d%d", &m, &s, &t);
  for (int i = 1; i <= t; ++i) {
    f[i] = f[i - 1];
    if (m > 9) {
      m -= 10;
      f[i] += 60;
    } else m += 4;
  }
  for (int i = 1; i <= t; ++i) {
    f[i] = ((f[i] > f[i - 1] + 17) ? f[i] : f[i - 1] + 17);
    if (f[i] >= s) {
      printf("Yes\n%d", i);
      return 0;
    }
  }
  printf("No\n%d", f[t]);
  return 0;
}
