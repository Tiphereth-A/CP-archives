#include <bits/stdc++.h>
#define M 200005
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
template <typename A>
A Max(const A &x, const A &y) {
  return x > y ? x : y;
}
template <typename A>
A Min(const A &x, const A &y) {
  return x < y ? x : y;
}
template <typename A>
void Swap(A &x, A &y) {
  x ^= y, y ^= x, x ^= y;
}
template <typename A>
A Abs(const A &x) {
  return x > 0 ? x : -x;
}
int f[M], a[M], n, ans = -999999;
int main() {
  scanf("%d", &n);
  _for(i, 1, n) {
    scanf("%d", &f[i]);
    a[i] = Max(a[i - 1] + f[i], f[i]);
    ans = Max(ans, a[i]);
  }
  printf("%d", ans);
  return 0;
}
