#include <bits/stdc++.h>
int main() {
  int n;
  scanf("%d", &n);
  while (n--) {
    int a;
    scanf("%d", &a);
    if (a & 1) printf("zs wins\n");
    else printf("pb wins\n");
  }
  return 0;
}
