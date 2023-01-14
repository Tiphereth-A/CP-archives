#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
template <typename A>
A Max(const A &x, const A &y) {
  return x > y ? x : y;
}
using namespace std;
const int M = 100005;
int l1, l2, n, a[M], f[M], g[M];
int main() {
  while (scanf("%d", &a[++n]) != EOF) continue;
  n--;
  if (n == 0) {
    printf("0\n0");
    return 0;
  }
  l1 = l2 = 1;
  f[1] = -a[1];
  g[1] = a[1];
  _for(i, 2, n) {
    if (-a[i] >= f[l1]) f[++l1] = -a[i];
    else {
      int j = std::upper_bound(f + 1, f + l1 + 1, -a[i]) - f;
      f[j] = -a[i];
    }
    if (a[i] > g[l2]) g[++l2] = a[i];
    else {
      int j = std::lower_bound(g + 1, g + l2 + 1, a[i]) - g;
      g[j] = a[i];
    }
  }
  printf("%d\n%d", l1, l2);
  return 0;
}
