#include <bits/stdc++.h>
typedef double db;
template <typename A>
A Abs(const A &x) {
  return x > 0 ? x : -x;
}
db A;
db F(db num) { return pow(num, A / num - num); }
db simpson(db a, db b) {
  db c = a + (b - a) / 2;
  return (F(a) + 4 * F(c) + F(b)) * (b - a) / 6;
}
db asr(db a, db b, db eps, db S) {
  db c = a + (b - a) / 2;
  db lS = simpson(a, c), rS = simpson(c, b);
  if (Abs(lS + rS - S) <= 15 * eps) return lS + rS + (lS + rS - S) / 15.0;
  return asr(a, c, eps / 2, lS) + asr(c, b, eps / 2, rS);
}
int main() {
  scanf("%lf", &A);
  if (A < 0) puts("orz");
  else if (A == 0) puts("1.99546");
  else printf("%.5lf", asr(0, 12, 1e-8, simpson(0, 12)));
  return 0;
}
