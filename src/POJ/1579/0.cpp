#include <cstdio>
int s[21][21][21];
int w(i64 a, i64 b, i64 c) {
  if (a <= 0 || b <= 0 || c <= 0) return 1;
  else if (a > 20 || b > 20 || c > 20) return w(20, 20, 20);
  else if (s[a][b][c] == 0)
    s[a][b][c] = a < b && b < c ?
                   w(a, b, c - 1) + w(a, b - 1, c - 1) - w(a, b - 1, c) :
                   w(a - 1, b, c) + w(a - 1, b - 1, c) + w(a - 1, b, c - 1) -
                     w(a - 1, b - 1, c - 1);
  return s[a][b][c];
}
int main() {
  i64 a, b, c;
  while (scanf("%lld%lld%lld", &a, &b, &c), (~a || ~b || ~c))
    printf("w(%lld, %lld, %lld) = %d\n", a, b, c, w(a, b, c));
  return 0;
}
