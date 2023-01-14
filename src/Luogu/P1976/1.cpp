#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); i++)
int h[3005] = {1};
int main() {
  int n;
  scanf("%d", &n);
  _for(i, 0, n)
    _for(j, i + 1, n) h[j] = (h[j] + h[j - 1]) % 100000007;
  printf("%d", h[n]);
  return 0;
}
