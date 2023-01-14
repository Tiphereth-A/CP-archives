#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
typedef double db;
typedef long double ldb;
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
  x ^= y ^= x ^= y;
}
template <typename A>
A Abs(const A &x) {
  return x > 0 ? x : -x;
}
template <typename A>
A Gcd(A x, A y) {
  return !y ? x : Gcd(y, x % y);
}
const int N = 200;
const db EPS = 1e-6;
char num[N];
int main() {
  const ldb lg2 = log10(2);
  while (~scanf("%s", num) && strcmp("0e0", num)) {
    ldb a = 0.0;
    int b = 0;
    *strchr(num, 'e') = ' ';
    sscanf(num, "%llf%d", &a, &b);
    a = log10(a) + b;
    _for(m, 0, 9) {
      ldb tmp1 = log10((1 << (m + 1)) - 1);
      _for(e, 1, 30) {
        ldb tmp2 = tmp1 + lg2 * ((1 << e) - m - 2);
        if (fabs(tmp2 - a) <= EPS) {
          printf("%d %d", m, e);
          goto _Fin;
        }
      }
    }
  _Fin:
    puts("");
  }
  return 0;
}
