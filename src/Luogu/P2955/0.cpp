#include <bits/stdc++.h>
int main() {
  long long n;
  scanf("%lld", &n);
  getchar();
  char c, x;
  while (n--) {
    while (((c = getchar()) != EOF) && c != '\n') x = c;
    x -= '0';
    if (x & 1) printf("odd\n");
    else printf("even\n");
  }
  return 0;
}
