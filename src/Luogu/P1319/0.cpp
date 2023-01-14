#include <bits/stdc++.h>
int a, n, t = 0, s = 0;
bool i;
int main() {
  scanf("%d", &n);
  int sqn = n * n;
  while (s < sqn) {
    scanf("%d", &a);
    i = !i;
    for (int b = a; b; --b, ++t, ++s) {
      if (t == n) {
        putchar('\n');
        t = 0;
      }
      if (i) putchar('0');
      else putchar('1');
    }
  }
  putchar('\n');
  return 0;
}
