#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-8;
double a, b, c, d;
bool check(double a, double b, double EPS) {
  if (fabs(a - b) < EPS) return true;
  return false;
}
double f(double x) { return (c * x + d) / (a * x + b); }
double simp(double l, double r) {
  double mid = (l + r) / 2.0;
  return (f(l) + 4.0 * f(mid) + f(r)) * (r - l) / 6.0;
}
double simpson(double l, double r, double EPS) {
  double mid = (l + r) / 2.0;
  double le = simp(l, mid);
  double ri = simp(mid, r);
  double all = simp(l, r);
  if (check(le + ri, all, EPS)) return all;
  return simpson(l, mid, EPS / 2.0) + simpson(mid, r, EPS / 2.0);
}
int main() {
  double l, r;
  cin >> a >> b >> c >> d >> l >> r;
  printf("%0.6lf", simpson(l, r, eps));
}
