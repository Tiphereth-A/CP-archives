#include <bits/stdc++.h>
#define _rfor(i, r, l) for (int i = (r); i >= (l); --i)
typedef long double ldb;
template <typename A>
A Abs(const A &x) {
  return x > 0 ? x : -x;
}
const ldb EPS = 1e-8l;
int n;
ldb a[14], l, r;
ldb F(ldb num) {
  ldb sum = 0;
  _rfor(i, n, 0) sum = sum * num + a[i];
  return sum;
}
ldb GoldSearch() {
  ldb mid1, mid2;
  mid1 = l + 0.38196601l * (r - l);
  mid2 = l + 0.61803399l * (r - l);
  do {
    if (F(mid1) < F(mid2)) {
      l = mid1;
      mid1 = mid2;
      mid2 = l + 0.61803399l * (r - l);
    } else {
      r = mid2;
      mid2 = mid1;
      mid1 = l + 0.38196601l * (r - l);
    }
  } while (Abs(r - l) > EPS);
  return l;
}
int main() {
  scanf("%d%Lf%Lf", &n, &l, &r);
  _rfor(i, n, 0) scanf("%Lf", a + i);
  printf("%.5Lf", GoldSearch());
  return 0;
}
