#include <bits/stdc++.h>
int main() {
  int n;
  scanf("%d", &n);
  int a[n + 1];
  for (int i = n; i >= 0; i--) scanf("%d", &a[i]);
  if (a[n] != 1 && a[n] != -1 && a[n] != 0) {
    printf("%dx^%d", a[n], n);
  } else if (a[n] == 1) {
    printf("x^%d", n);
  } else if (a[n] == -1) {
    printf("-x^%d", n);
  }
  for (int i = n - 1; i > 0; i--) {
    if (a[i] > 0) {
      printf("+");
      if (a[i] != 1) printf("%d", a[i]);
      if (i != 1) {
        printf("x^%d", i);
      } else printf("x");
    } else if (a[i] < 0) {
      if (a[i] != -1) printf("%d", a[i]);
      else printf("-");
      if (i != 1) {
        printf("x^%d", i);
      } else printf("x");
    }
  }
  if (a[0] > 0) printf("+");
  if (a[0] != 0) printf("%d\n", a[0]);
  return 0;
}
