#include <bits/stdc++.h>
template <class Tp>
Tp dec(Tp &i) {
  return --i;
}
template <class Tp>
Tp inc(Tp &i) {
  return ++i;
}
#define(std::cerr << __LINE__ << ' ' << __FUNCTION__ << std::endl)
using namespace std;
class RombergSolver {
private:
  std::function<double(double)> f;
  double ctqf(double a, double b, double h) const {
    double ans = 0;
    for (double i = a + h * .5; i < b; i += h) ans += f(i);
    return ans;
  }

public:
  template <typename Func>
  RombergSolver(Func &&func): f(func) {}
  double operator()(double a, double b, double eps) const {
    double h = b - a;
    double T1 = (f(a) + f(b)) * h * .5, T2 = 0, S1 = 0, S2 = 0, C1 = 0, C2 = 0,
           R1 = 0, R2 = 0;
    for (int k = 1; k < 4; h *= .5, ++k) {
      T2 = (T1 + h * ctqf(a, b, h)) * .5;
      S2 = (4 * T2 - T1) / 3;
      T1 = T2;
      if (k == 1) {
        S1 = S2;
        continue;
      };
      C2 = (16 * S2 - S1) / 15;
      if (k == 2) {
        C1 = C2;
        continue;
      };
      R1 = (64 * C2 - C1) / 63;
    }
    for (;; h /= 2, T1 = T2, S1 = S2, C1 = C2, R1 = R2)
      if (std::abs(
            R1 -
            (R2 =
               (64 *
                  (C2 = (16 * (S2 = (4 * (T2 = (T1 + h * ctqf(a, b, h)) * .5) -
                                     T1) /
                                    3) -
                         S1) /
                        15) -
                C1) /
               63)) < eps)
        break;
    return R2;
  }
};
const double EPS = 1e-9;
void solve(int t_ = 0) {
  double D, H, B, L;
  cin >> D >> H >> B >> L;
  int n = (B - 1) / D + 1;
  L /= n;
  double W = B / n;
  double l = 0, r = H;
  while (r - l > EPS)
    if (double mid = (l + r) / 2; RombergSolver([mid, W](double x) -> double {
                                    auto _ = 4 * mid / (W * W) * 2 * x;
                                    return sqrt(1 + _ * _);
                                  })(0, W / 2, EPS) <= L / 2)
      l = mid;
    else r = mid;
  cout << "Case " << t_ + 1 << ":\n" << H - l << '\n';
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  cout << fixed << setprecision(2);
  int t_ = 0;
  std::cin >> t_;
  for (i_ = 0; i_ < t_; ++i_) {
    solve(i_);
    if (i_ < t_ - 1) cout << '\n';
  }
  return 0;
}
