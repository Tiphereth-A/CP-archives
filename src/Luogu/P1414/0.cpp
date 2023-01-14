#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define Max(a, b) (((a) > (b)) ? (a) : (b))
#define MAXN 1000005
int c[MAXN], n;
int main() {
  scanf("%d", &n);
  int m = 0;
  _for(i, 1, n) {
    int x;
    scanf("%d", &x);
    m = Max(m, x);
    int sqx = sqrt(x);
    _for(i, 1, sqx) {
      if (x % i == 0) {
        ++c[i];
        if (x != i * i) ++c[x / i];
      }
    }
  }
  _for(i, 1, n) {
    while (c[m] < i) m--;
    printf("%d\n", m);
  }
  return 0;
}
