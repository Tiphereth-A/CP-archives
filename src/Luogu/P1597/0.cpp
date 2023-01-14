#include <bits/stdc++.h>
int a[3];
char c1, c2;
int main() {
  if (scanf("%c:=%c;", &c1, &c2) == 2) {
    a[c1 - 'a'] = ((c2 >= '0' && c2 <= '9') ? (c2 - '0') : a[c2 - 'a']);
    main();
  } else printf("%d %d %d", a[0], a[1], a[2]);
}
