#include <cstdio>
#include <iostream>
using namespace std;
void exgcd(i64 a, i64 b, i64 &gcd, i64 &x, i64 &y) {
  if (!b) {
    gcd = a;
    x = 1;
    y = 0;
    return;
  }
  exgcd(b, a % b, gcd, y, x);
  y -= a / b * x;
}
int main() {
  i64 a, b, c, k;
  while ((cin >> a >> b >> c >> k) && (a || b || c || k)) {
    i64 m = 1ll << k;
    i64 _ = b - a;
    i64 g, x, y;
    exgcd(c, m, g, x, y);
    if (_ % g) {
      puts("FOREVER");
      continue;
    }
    (((x *= _ / g) %= m) += m) %= m / g;
    cout << x << endl;
  }
}
