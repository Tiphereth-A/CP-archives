#include <bits/stdc++.h>
using namespace std;
i64 exgcd(i64 a, i64 b, i64 &x, i64 &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  i64 res = exgcd(b, a % b, y, x);
  y -= a / b * x;
  return res;
}
int main() {
  int kase;
  scanf("%d", &kase);
  i64 a, b, c, d, x, y;
  i64 min_x, min_y, max_x, max_y;
  while (kase--) {
    scanf("%lld%lld%lld", &a, &b, &c);
    if (c % (d = exgcd(a, b, x, y))) {
      puts("-1");
      continue;
    }
    x *= c / d;
    y *= c / d;
    min_x = (x % (b / d) + (b / d)) % (b / d);
    if (!min_x) min_x = b / d;
    max_y = (c - a * min_x) / b;
    min_y = (y % (a / d) + (a / d)) % (a / d);
    if (!min_y) min_y = a / d;
    max_x = (c - b * min_y) / a;
    if (max_y <= 0) printf("%lld %lld\n", min_x, min_y);
    else
      printf("%lld %lld %lld %lld %lld\n",
             (max_x - min_x) * d / b + 1,
             min_x,
             min_y,
             max_x,
             max_y);
  }
  return 0;
}
