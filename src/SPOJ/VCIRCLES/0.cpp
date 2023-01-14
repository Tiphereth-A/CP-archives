#include <bits/stdc++.h>
using ll = long long;
using pii = std::pair<int, int>;
template <class Tp>
using vc = std::vector<Tp>;
#define for_(i, l, r, v...) for (ll i = (l), i##e = (r), ##v; i <= i##e; ++i)
template <class Tp>
Tp dec(Tp &i) {
  return --i;
}
template <class Tp>
Tp inc(Tp &i) {
  return ++i;
}
const double EPS = 1e-7;
using namespace std;
struct Node {
  pii p;
  int r;
  Node(pii const &p = {0, 0}, int r = 0): p(p), r(r) {}
};
class SimpsonSolver {
private:
  std::function<double(double)> f;
  static constexpr double
  simpson(double l, double r, double fl, double fmid, double fr) {
    return (fl + 4 * fmid + fr) * (r - l) / 6;
  }
  double asr(double l, double r, double area, double eps) const {
    double mid = r - (r - l) * .5;
    double lmid = mid - (mid - l) * .5, rmid = r - (r - mid) * .5;
    double fl = f(l), flmid = f(lmid), fmid = f(mid), frmid = f(rmid),
           fr = f(r);
    double ls = simpson(l, mid, fl, flmid, fmid),
           rs = simpson(mid, r, fmid, frmid, fr);
    if (std::abs(ls + rs - area) <= 15 * eps)
      return ls + rs + (ls + rs - area) / 15;
    return asr(l, mid, ls, eps * .5) + asr(mid, r, rs, eps * .5);
  }

public:
  template <typename Func>
  SimpsonSolver(Func &&func): f(func) {}
  double operator()(double l, double r, double eps) const {
    return asr(l, r, simpson(l, r, f(l), f(r - (r - l) * .5), f(r)), eps);
  }
};
void solve(int t_ = 0) {
  int n;
  cin >> n;
  vc<Node> v(n);
  for (auto &c : v) cin >> c.p.first >> c.p.second >> c.r;
  vc<pair<double, double>> seg;
  seg.reserve(n);
  auto f = [&](double x) -> double {
    seg.clear();
    for (auto &&c : v) {
      if (abs(x - c.p.first) > c.r) continue;
      double _ = sqrt(c.r * c.r - abs(x - c.p.first) * abs(x - c.p.first));
      seg.emplace_back(c.p.second - _, c.p.second + _);
    }
    if (seg.empty()) return 0;
    sort(seg.begin(), seg.end());
    double ans = 0, lst = seg.front().first;
    for (auto &&i : seg)
      if (i.second - lst > 0) {
        ans += i.second - max(i.first, lst);
        lst = i.second;
      }
    return ans;
  };
  vector<int> pos;
  pos.reserve(n * 2);
  for (auto &&i : v) {
    pos.push_back(i.p.first - i.r);
    pos.push_back(i.p.first + i.r);
  }
  sort(pos.begin(), pos.end());
  pos.erase(unique(pos.begin(), pos.end()), pos.end());
  double ans = 0;
  for_(i, 1, pos.size() - 1) ans += SimpsonSolver(f)(pos[i - 1], pos[i], EPS);
  cout << fixed << setprecision(5) << ans << '\n';
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  solve(i_);
  return 0;
}
