#include <bits/stdc++.h>
#define for_(i, l, r, vars...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vars; i <= i##end; ++i)
using namespace std;
class SimpsonSolver {
protected:
  const double eps__;
  const int least_dep__;
  template <typename Func>
  constexpr double simpson(double l, double r, Func &&func) const {
    return (func(l) + 4 * func(r - (r - l) * .5) + func(r)) * (r - l) / 6;
  }
  template <typename Func>
  double
  asr(double l, double r, double area, double eps, int dep, Func &&func) const {
    double mid = r - (r - l) * .5;
    double ls = simpson(l, mid, func), rs = simpson(mid, r, func);
    if (std::abs(ls + rs - area) <= 15 * eps && dep < 0)
      return ls + rs + (ls + rs - area) / 15;
    return asr(l, mid, ls, eps * .5, dep - 1, func) +
           asr(mid, r, rs, eps * .5, dep - 1, func);
  }

public:
  SimpsonSolver(double eps, int least_dep)
    : eps__(eps), least_dep__(least_dep) {}
  template <typename Func>
  double operator()(double l, double r, Func &&func) const {
    return asr(l, r, simpson(l, r, func), eps__, least_dep__, func);
  }
} simpson_solver(1e-6, 8);
namespace FFT {
using CP = std::complex<double>;
const double PI = acos(-1.0);
size_t n = 0;
std::vector<size_t> rev;
void init(size_t m) {
  if (n > m) return;
  n = 1;
  int k = 0;
  while (n <= m) {
    n <<= 1;
    ++k;
  }
  rev.resize(n);
  for (int i = 0; i < n; ++i)
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
}
void dft(std::vector<CP> &a, int op) {
  for (int i = 0; i < n; ++i)
    if (rev[i] > i) std::swap(a[rev[i]], a[i]);
  for (int i = 1; i < n; i <<= 1) {
    CP now(std::cos(PI / i), op * std::sin(PI / i));
    for (int j = 0, p = (i << 1); j < n; j += p) {
      CP w(1, 0);
      for (int k = 0; k < i; ++k, w = w * now) {
        CP x = a[j + k], y = a[j + k + i] * w;
        a[j + k] = x + y;
        a[j + k + i] = x - y;
      }
    }
  }
  if (op == -1)
    for (int i = 0; i < n; ++i) a[i] = {a[i].real() / n, a[i].imag() / n};
}
std::vector<double> conv(std::vector<double> const &a,
                         std::vector<double> const &b) {
  init(a.size() + b.size() - 1);
  std::vector<CP> a_(n), b_(n), c_(n);
  for (size_t i = 0; i < a.size(); ++i) a_[i] = a[i];
  for (size_t i = 0; i < b.size(); ++i) b_[i] = b[i];
  dft(a_, 1);
  dft(b_, 1);
  for (size_t i = 0; i < n; ++i) c_[i] = a_[i] * b_[i];
  dft(c_, -1);
  std::vector<double> c(a.size() + b.size() - 1);
  for (size_t i = 0; i < a.size() + b.size() - 1; ++i) c[i] = c_[i].real();
  return c;
}
}  // namespace FFT
using FFT::conv;
std::vector<double> qpow(std::vector<double> a, uint64_t b) {
  std::vector<double> res{1};
  for (; b; b >>= 1, a = conv(a, a))
    if (b & 1) res = conv(res, a);
  return res;
};
const uint32_t OFFSET = 5;
const uint32_t N = 3e5 + OFFSET;
auto solve([[maybe_unused]] int t_ = 0) -> void {
  int x, y;
  cin >> x >> y;
  if (x * y < N) {
    vector<double> f = qpow(vector<double>(x, 1. / x), y);
    for_(i, 1, f.size() - 1) f[i] += f[i - 1];
    for_(i, 1, 10, a, b) {
      cin >> a >> b;
      cout << f[b] - (a ? f[a - 1] : 0) << '\n';
    }
  } else {
    const double ymu = (x - 1) * .5 * y,
                 ystdi = 1. / sqrt((x * x - 1) / 12. * y);
    auto norm = [ymu, ystdi](double x) -> double { return (x - ymu) * ystdi; };
    auto f = [](double x) -> double {
      return exp(-x * x * .5) / sqrt(2 * acos(-1.));
    };
    for_(i, 1, 10, a, b) {
      cin >> a >> b;
      cout << simpson_solver(norm(a), norm(b), f) << '\n';
    }
  }
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  std::cout << std::fixed << std::setprecision(12);
  int t_ = 0;
  std::cin >> t_;
  for (i_ = 0; i_ < t_; ++i_) solve(i_);
  return 0;
}
