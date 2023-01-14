#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using data_t = double;
constexpr data_t EPS = 1e-8;
constexpr ptrdiff_t sgn(data_t lhs) { return lhs < -EPS ? -1 : lhs > EPS; }
constexpr bool is_negative(data_t x) { return sgn(x) & 2; }
constexpr bool is_zero(data_t x) { return !sgn(x); }
constexpr bool is_positive(data_t x) { return (sgn(x) + 1) & 2; }
constexpr ptrdiff_t comp(data_t lhs, data_t rhs) { return sgn(lhs - rhs); }
constexpr bool is_less(data_t lhs, data_t rhs) {
  return is_negative(lhs - rhs);
}
constexpr bool is_equal(data_t lhs, data_t rhs) { return is_zero(lhs - rhs); }
constexpr bool is_greater(data_t lhs, data_t rhs) {
  return is_positive(lhs - rhs);
}
enum RELA_CC { lyingin_cc, touchin_cc, intersect_cc, touchex_cc, lyingout_cc };
enum RELA_CP { outside_cp, onborder_cp, inside_cp };
struct Point {
  data_t x, y;
  constexpr Point(data_t x = data_t{}, data_t y = data_t{}): x(x), y(y) {}
  constexpr Point &operator*=(data_t n) {
    this->x *= n;
    this->y *= n;
    return *this;
  }
  constexpr Point operator*(data_t n) const { return Point(*this) *= n; }
  constexpr Point &operator/=(data_t n) {
    this->x /= n;
    this->y /= n;
    return *this;
  }
  constexpr Point operator/(data_t n) const { return Point(*this) /= n; }
  constexpr Point &operator+=(const Point &rhs) {
    this->x += rhs.x;
    this->y += rhs.y;
    return *this;
  }
  constexpr Point operator+(const Point &rhs) const {
    return Point(*this) += rhs;
  }
  constexpr Point &operator-=(const Point &rhs) {
    this->x -= rhs.x;
    this->y -= rhs.y;
    return *this;
  }
  constexpr Point operator-(const Point &rhs) const {
    return Point(*this) -= rhs;
  }
  constexpr Point operator-() const { return Point{-x, -y}; }
  constexpr bool operator<(const Point &rhs) const {
    auto c = comp(x, rhs.x);
    if (c) return c >> 1;
    return comp(y, rhs.y) >> 1;
  }
  friend constexpr data_t operator^(const Point &lhs, const Point &rhs) {
    return lhs.x * rhs.y - lhs.y * rhs.x;
  }
  friend constexpr data_t cross_mul(const Point &lhs, const Point &rhs) {
    return lhs ^ rhs;
  }
  constexpr auto norm() const { return x * x + y * y; };
  constexpr auto abs() const { return sqrt(norm()); };
  constexpr Point &do_rot90() {
    data_t tmp = x;
    x = -y;
    y = tmp;
    return *this;
  };
  constexpr Point &do_unit() { return *this /= abs(); };
};
constexpr data_t dist_PP(const Point &lhs, const Point &rhs) {
  return std::hypot(lhs.x - rhs.x, lhs.y - rhs.y);
}
constexpr data_t cross(const Point &p1, const Point &p2, const Point &p3) {
  return (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
}
constexpr ptrdiff_t
sgn_cross(const Point &p1, const Point &p2, const Point &p3) {
  return sgn(cross(p1, p2, p3));
}
struct Circle {
  Point o;
  data_t r;
  Circle() = default;
  constexpr Circle(const data_t &c_x, const data_t &c_y, data_t r_)
    : o(c_x, c_y), r(r_) {}
  constexpr RELA_CC relation_C(const Circle &c2) const {
    data_t d = dist_PP(o, c2.o);
    if (is_greater(d, r + c2.r)) return RELA_CC::lyingout_cc;
    if (is_equal(d, r + c2.r)) return RELA_CC::touchex_cc;
    if (is_greater(d, std::abs(r - c2.r))) return RELA_CC::intersect_cc;
    if (is_equal(d, std::abs(r - c2.r))) return RELA_CC::touchin_cc;
    return RELA_CC::lyingin_cc;
  }
  constexpr RELA_CP relation_P(const Point &p) const {
    data_t d = dist_PP(o, p);
    if (is_less(d, r)) return RELA_CP::inside_cp;
    if (is_equal(d, r)) return RELA_CP::onborder_cp;
    return RELA_CP::outside_cp;
  }
};
vector<Point> ins_CC(const Circle &c1, const Circle &c2) {
  assert(!is_equal(c1.o.x, c2.o.x) || !is_equal(c1.o.y, c2.o.y) ||
         !is_equal(c1.r, c2.r));
  auto state = c1.relation_C(c2);
  if (state == RELA_CC::lyingin_cc || state == RELA_CC::lyingout_cc) return {};
  data_t d = std::min(dist_PP(c1.o, c2.o), c1.r + c2.r);
  data_t y = (c1.r * c1.r - c2.r * c2.r + d * d) / (2 * d),
         x = sqrt(c1.r * c1.r - y * y);
  Point dr = (c2.o - c1.o).do_unit();
  Point q1 = c1.o + dr * y, q2 = dr.do_rot90() * x;
  return {q1 - q2, q1 + q2};
}
struct ConvexHull {
  vector<Point> vs;
  size_t next(size_t idx) const { return idx + 1 == vs.size() ? 0 : idx + 1; }
  explicit ConvexHull(const vector<Point> &vs_): vs(vs_) {
    ptrdiff_t sz = vs.size();
    if (sz <= 1) return;
    std::sort(vs.begin(), vs.end());
    vector<Point> cvh(sz * 2);
    ptrdiff_t sz_cvh = 0;
    for (ptrdiff_t i = 0; i < sz; cvh[sz_cvh++] = vs[i++])
      while (sz_cvh > 1 &&
             sgn_cross(cvh[sz_cvh - 2], cvh[sz_cvh - 1], vs[i]) <= 0)
        --sz_cvh;
    for (ptrdiff_t i = sz - 2, t = sz_cvh; ~i; cvh[sz_cvh++] = vs[i--])
      while (sz_cvh > t &&
             sgn_cross(cvh[sz_cvh - 2], cvh[sz_cvh - 1], vs[i]) <= 0)
        --sz_cvh;
    cvh.resize(sz_cvh - 1);
    vs = cvh;
  }
  data_t diameter() const {
    size_t sz = vs.size();
    if (sz <= 1) return data_t{};
    size_t is = 0, js = 0;
    for (size_t k = 1; k < sz; ++k) {
      is = vs[k] < vs[is] ? k : is;
      js = vs[js] < vs[k] ? k : js;
    }
    size_t i = is, j = js;
    data_t ret = dist_PP(vs[i], vs[j]);
    do {
      (++(cross_mul(vs[next(i)] - vs[i], vs[next(j)] - vs[j]) >= 0 ? j : i)) %=
        sz;
      ret = std::max(ret, dist_PP(vs[i], vs[j]));
    } while (i != is || j != js);
    return ret;
  }
};
auto solve([[maybe_unused]] int t_ = 0) -> void {
  i64 n, r;
  cin >> n >> r;
  Circle c0(0, 0, r);
  vector<Circle> vc;
  for (i64 i = 1, xx, yy, rr; i <= n; ++i) {
    cin >> xx >> yy >> rr;
    Circle c1(xx, yy, rr);
    auto ans = c0.relation_C(c1);
    if (ans != RELA_CC::intersect_cc) continue;
    vc.push_back(c1);
  }
  vector<Point> vp1;
  for (auto const &c : vc) {
    auto ps = ins_CC(c0, c);
    for (auto const &p : ps) {
      vp1.push_back(p);
      vp1.push_back(-p);
    }
  }
  vector<Point> vp;
  for (auto const &p : vp1) {
    bool f = 0;
    for (auto const &c : vc)
      if (c.relation_P(p) == RELA_CP::inside_cp) {
        f = 1;
        break;
      }
    if (f) continue;
    vp.push_back(p);
  }
  cout << ConvexHull(vp).diameter() << '\n';
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  cout << fixed << setprecision(15);
  int t_ = 0;
  std::cin >> t_;
  for (i_ = 0; i_ < t_; ++i_) {
    cout << "Case #" << i_ + 1 << ": ";
    solve(i_);
  }
  return 0;
}
