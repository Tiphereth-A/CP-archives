#include <bits/stdc++.h>
int n, i;
char x[101], z[101];
int main() {
  scanf("%d%s%s", &n, x, z);
  for (i = 0; i < n; i++) {
    if (x[i] < z[i]) {
      printf("%d", -1);
      return 0;
    }
  }
  for (i = 0; i < n; i++) printf("%c", z[i]);
  return 0;
}
