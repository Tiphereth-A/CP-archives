#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 3e5 + 5;
double a[N], b[N];
int main() {
  int n;
  scanf("%d\n", &n);
  _for(i, 1, n) {
    char c;
    while (((c = getchar()) != 'o') && (c != 'x') && (c != '?'));
    double p = (c == 'o') ? 1 : (c == 'x' ? 0 : 0.5);
    a[i] = (a[i - 1] + 1) * p;
    b[i] = (2 * a[i - 1] + 1) * p + b[i - 1];
  }
  printf("%.4lf", b[n]);
  return 0;
}
