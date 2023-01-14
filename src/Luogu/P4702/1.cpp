#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
int n, a;
unsigned long long sum;
int main() {
  scanf("%d", &n);
  _for(i, 1, n) {
    scanf("%d", &a);
    sum += a;
  }
  if (sum & 1) printf("Alice");
  else printf("Bob");
  return 0;
}
