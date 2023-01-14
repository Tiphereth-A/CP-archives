#include <bits/stdc++.h>
typedef double db;
template <typename A>
A Abs(const A &x) {
  return x > 0 ? x : -x;
}
db A, B, C, D, L, R;
db F(db num) { return (C * num + D) / (A * num + B); }
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
  scanf("%lf%lf%lf%lf%lf%lf", &A, &B, &C, &D, &L, &R);
  printf("%.6lf", asr(L, R, 1e-6, simpson(L, R)));
  return 0;
}
