#include <bits/stdc++.h>
using namespace std;
const int N = 505;
int n;
struct Circle {
  double x, r;
  bool in_range(double pos) { return x - r <= pos && x + r >= pos; }
  double get_y(double pos) { return sqrt(r * r - abs(pos - x) * abs(pos - x)); }
} cir[N];
struct Trapezoid {
  double l, r;
  double len_l, len_r;
  Trapezoid() {}
  Trapezoid(double _l, double _r, int i): l(_l), r(_r) {
    len_l = cir[i].get_y(l);
    len_r = i < n ? cir[i + 1].get_y(r) : 0;
  }
  bool in_range(double pos) { return l <= pos && r >= pos; }
  double get_y(double pos) {
    return ((r - pos) * len_l + (pos - l) * len_r) / (r - l);
  }
} trp[N];
double f(double x) {
  double ans = 0;
  for (int i = 1; i <= n; ++i)
    if (cir[i].in_range(x)) ans = max(ans, cir[i].get_y(x));
  for (int i = 1; i <= n; ++i)
    if (trp[i].in_range(x)) ans = max(ans, trp[i].get_y(x));
  return ans;
}
double asr(double l, double r) {
  return (f(l) + 4 * f((l + r) / 2) + f(r)) * (r - l) / 6;
}
double simpson(double l, double r, double ans, double eps = 1e-6) {
  double mid = (l + r) / 2;
  double sl = asr(l, mid), sr = asr(mid, r);
  if (abs(sl + sr - ans) < eps * 15) return sl + sr - (sl + sr - ans) / 15;
  return simpson(l, mid, sl, eps / 2) + simpson(mid, r, sr, eps / 2);
}
double h[N], r[N];
int main() {
  double alpha;
  cin >> n >> alpha;
  for (int i = 0; i <= n; ++i) cin >> h[i];
  for (int i = 1; i <= n; ++i) cin >> r[i];
  double cot_alpha = 1.0 / tan(alpha), sum_h = 0;
  double L = DBL_MAX, R = DBL_MIN;
  for (int i = 1; i <= n; ++i) {
    cir[i] = {sum_h * cot_alpha, r[i]};
    sum_h += h[i];
    L = min(L, cir[i].x - cir[i].r);
    R = max(R, cir[i].x + cir[i].r);
  }
  R = max(R, sum_h * cot_alpha);
  sum_h = 0;
  for (int i = 1; i <= n; ++i) {
    double cos_theta = (r[i + 1] - r[i]) / (h[i] * cot_alpha);
    double delta_l = r[i] * cos_theta, delta_r = r[i + 1] * cos_theta;
    trp[i] = Trapezoid(
      sum_h * cot_alpha - delta_l, (sum_h + h[i]) * cot_alpha - delta_r, i);
    sum_h += h[i];
  }
  printf("%.2f", simpson(L, R, asr(L, R)) * 2);
  return 0;
}
