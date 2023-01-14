#include <bits/stdc++.h>
int main() {
  int n;
  while (1) {
    scanf("%d", &n);
    if (n == 0) return 0;
    if (n & 1) printf("Bob\n");
    else printf("Alice\n");
  }
  return 0;
}
