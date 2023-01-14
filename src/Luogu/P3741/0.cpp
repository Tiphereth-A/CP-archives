#include <bits/stdc++.h>
char a[550];
int main() {
  gets(a);
  gets(a);
  int ans = 0;
  for (int i = 0, len = strlen(a); i < len; i++) {
    if (a[i] == 'V' && a[i + 1] == 'K') {
      ++ans;
      a[i] = a[i + 1] = 'X';
    }
  }
  for (int i = 0, len = strlen(a); i < len; i++) {
    if (a[i] != 'X' && a[i] == a[i + 1]) {
      ++ans;
      break;
    }
  }
  printf("%d", ans);
  return 0;
}
