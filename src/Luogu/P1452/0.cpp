#include <bits/extc++.h>
using namespace std;
template <typename Tp>
using vc = std::vector<Tp>;
#define foreach_ref_(i, container) for (auto &i : (container))
#define read_var_(type, name) \
  type name;                  \
  std::cin >> name
#define read_container_(type, name, size) \
  type name(size);                        \
  foreach_ref_(i, name) std::cin >> i;
template <class Tp>
auto chkmin(Tp &a, Tp b) -> bool {
  return b < a ? a = b, true : false;
};
template <class Tp>
auto chkmax(Tp &a, Tp b) -> bool {
  return a < b ? a = b, true : false;
};
template <typename Tp>
auto discretization(Tp &var) -> Tp {
  Tp d__(var);
  std::sort(d__.begin(), d__.end());
  d__.erase(std::unique(d__.begin(), d__.end()), d__.end());
  for (auto &i : var)
    i = std::distance(d__.begin(), std::lower_bound(d__.begin(), d__.end(), i));
  return d__;
};
template <typename Tp>
auto ispow2(Tp i) -> bool {
  return i && (i & -i) == i;
}
template <class Tp, class Up>
std::ostream &operator<<(std::ostream &os, const std::pair<Tp, Up> &p) {
  if (&os == &std::cerr) return os << "(" << p.first << ", " << p.second << ")";
  return os << p.first << " " << p.second;
}
template <class Ch, class Tr, class Container>
std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os,
                                       const Container &x) {
  if (&os == &std::cerr) os << "[";
  if (&os == &std::cerr)
    for (auto it = x.begin(); it != x.end() - 1; ++it) os << *it << ", ";
  else
    for (auto it = x.begin(); it != x.end() - 1; ++it) os << *it << ' ';
  os << x.back();
  if (&os == &std::cerr) os << "]";
  return os;
}
const double EPS = 1e-6;
namespace calc_geo {
using data_t = double;
template <typename Tp>
using cont_t = std::vector<Tp>;
constexpr data_t EPS = 1e-9;
constexpr ptrdiff_t sign(data_t lhs) { return lhs < -EPS ? -1 : lhs > EPS; }
constexpr bool is_negative(data_t x) { return sign(x) & 2; }
constexpr bool is_zero(data_t x) { return !sign(x); }
constexpr bool is_positive(data_t x) { return !(sign(x) >> 1); }
constexpr ptrdiff_t comp(data_t lhs, data_t rhs) { return sign(lhs - rhs); }
constexpr bool is_less(data_t lhs, data_t rhs) {
  return is_negative(lhs - rhs) & 2;
}
constexpr bool is_equal(data_t lhs, data_t rhs) { return is_zero(lhs - rhs); }
constexpr bool is_greater(data_t lhs, data_t rhs) {
  return is_positive(lhs - rhs);
}
constexpr bool is_intersect(data_t l1, data_t r1, data_t l2, data_t r2) {
  if (l1 > r1) {
    auto tmp = l1;
    l1 = r1;
    r1 = tmp;
  }
  if (l2 > r2) {
    auto tmp = l2;
    l2 = r2;
    r2 = tmp;
  }
  return !(is_less(r1, l2) || is_less(r2, l1));
}
constexpr bool is_in_middle(data_t l, data_t mid, data_t r) {
  return is_equal(l, mid) || is_equal(r, mid) || ((l < mid) ^ (r < mid));
}
struct Point2 {
  using self = Point2;
  data_t x, y;
  constexpr Point2(data_t x = data_t{}, data_t y = data_t{}): x(x), y(y) {}
  friend istream &operator>>(istream &is, self &rhs) {
    return is >> rhs.x >> rhs.y;
  }
  friend ostream &operator<<(ostream &os, const self &rhs) {
    return os << rhs.x << ' ' << rhs.y;
  }
  friend constexpr self polar(data_t r, data_t theta) {
    return self{r * cos(theta), r * sin(theta)};
  }
  friend constexpr self lerp(const self &lhs, const self &rhs, data_t coord) {
    return lhs * coord + rhs * (1 - coord);
  }
  friend constexpr self mid_point(const self &lhs, const self &rhs) {
    return lerp(lhs, rhs, 0.5);
  }
#define SCALA_OP(op)                         \
  constexpr self &operator op##=(data_t n) { \
    this->x op## = n;                        \
    this->y op## = n;                        \
    return *this;                            \
  }                                          \
  constexpr self operator op(data_t n) const { return self(*this) op## = n; }
  SCALA_OP(+)
  SCALA_OP(-)
  SCALA_OP(*)
  SCALA_OP(/)
#undef SCALA_OP
#define VEC_OP(op)                                    \
  constexpr self &operator op##=(const self & rhs) {  \
    this->x op## = rhs.x;                             \
    this->y op## = rhs.y;                             \
    return *this;                                     \
  }                                                   \
  constexpr self operator op(const self &rhs) const { \
    return self(*this) op## = rhs;                    \
  }
  VEC_OP(+)
  VEC_OP(-)
#undef VEC_OP
  constexpr self operator-() const { return self{-x, -y}; }
  constexpr bool operator<(const self &rhs) const {
    auto c = comp(x, rhs.x);
    if (c) return c >> 1;
    return comp(y, rhs.y) >> 1;
  }
  constexpr bool operator==(const self &rhs) const {
    return is_equal(x, rhs.x) && is_equal(y, rhs.y);
  }
  friend constexpr data_t dot_mul(const self &lhs, const self &rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
  }
  friend constexpr data_t cross_mul(const self &lhs, const self &rhs) {
    return lhs.x * rhs.y - lhs.y * rhs.x;
  }
#define SCALA_FUNC(name, func_body)      \
  constexpr auto name() const func_body; \
  friend constexpr auto name(const self &lhs) { return lhs.name(); }
  SCALA_FUNC(arg, { return atan2(y, x); })
  SCALA_FUNC(norm, { return x * x + y * y; })
  SCALA_FUNC(abs, { return sqrt(norm()); })
  SCALA_FUNC(quad, { return sign(y) + sign(x) >= 1; })
#undef SCALA_FUNC
#define SELF_FUNC(name, func_body)       \
  constexpr self &do_##name() func_body; \
  friend constexpr self name(self lhs) { return lhs.do_##name(); }
  SELF_FUNC(rotate90, {
    data_t tmp = x;
    x = -y;
    y = tmp;
    return *this;
  })
  SELF_FUNC(rotate180, {
    x = -x;
    y = -y;
    return *this;
  })
  SELF_FUNC(rotate270, {
    data_t tmp = y;
    y = -x;
    x = tmp;
    return *this;
  })
  SELF_FUNC(unit, { return *this /= abs(); })
#undef SELF_FUNC
  constexpr self &do_rotate(data_t theta) {
    data_t _x = x, _y = y;
    x = _x * cos(theta) - _y * sin(theta);
    y = _x * sin(theta) + _y * cos(theta);
    return *this;
  };
  friend constexpr self rotate(self lhs, data_t theta) {
    return lhs.do_rotate(theta);
  }
};
constexpr data_t dist_PP(const Point2 &lhs, const Point2 &rhs) {
  return hypot(lhs.x - rhs.x, lhs.y - rhs.y);
}
constexpr data_t sqr_dist_PP(const Point2 &lhs, const Point2 &rhs) {
  return (lhs.x - rhs.x) * (lhs.x - rhs.x) + (lhs.y - rhs.y) * (lhs.y - rhs.y);
}
constexpr data_t cross(const Point2 &p1, const Point2 &p2, const Point2 &p3) {
  return (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
}
constexpr ptrdiff_t
cross_sign(const Point2 &p1, const Point2 &p2, const Point2 &p3) {
  return sign(cross(p1, p2, p3));
}
constexpr bool is_in_middle(Point2 a, Point2 m, Point2 b) {
  return is_in_middle(a.x, m.x, b.x) && is_in_middle(a.y, m.y, b.y);
}
constexpr data_t ang_PP(const Point2 &p1, const Point2 &p2) {
  return atan2(cross_mul(p1, p2), dot_mul(p1, p2));
}
struct Polynomial2 {
  using self = Polynomial2;
  using point_t = Point2;
  cont_t<point_t> vertice;
  Polynomial2(const cont_t<point_t> &_vertice): vertice(_vertice) {}
  friend istream &operator>>(istream &is, self &rhs) {
    for (auto &i : rhs.vertice) is >> i;
    return is;
  }
  friend ostream &operator<<(ostream &os, const self &rhs) {
    for (auto it = rhs.vertice.begin(); it != rhs.vertice.end() - 1; ++it)
      os << *it << ' ';
    return os << rhs.vertice.back();
  }
  self &resort() {
    std::sort(vertice.begin(), vertice.end());
    return *this;
  }
  self &reunique() {
    resort();
    vertice.erase(std::unique(vertice.begin(), vertice.end()), vertice.end());
    return *this;
  }
  point_t &operator[](size_t x) { return vertice[x]; }
  const point_t &operator[](size_t x) const { return vertice[x]; }
#define SCALA_FUNC(name, func_body) \
  auto name() const func_body;      \
  friend auto name(const self &lhs) { return lhs.name(); }
  SCALA_FUNC(area, {
    data_t result = 0;
    size_t sz = vertice.size();
    for (size_t i = 0; i < sz; ++i)
      result += cross_mul(vertice[i], vertice[(i + 1) % sz]);
    return result / 2;
  })
  SCALA_FUNC(convex_diameter, {
    size_t sz = vertice.size();
    if (sz <= 1) return data_t{};
    size_t is = 0;
    size_t js = 0;
    for (size_t k = 1; k < sz; ++k) {
      is = vertice[k] < vertice[is] ? k : is;
      js = vertice[js] < vertice[k] ? k : js;
    }
    size_t i = is;
    size_t j = js;
    data_t ret = sqr_dist_PP(vertice[i], vertice[j]);
    do {
      (++(cross_mul(vertice[(i + 1) % sz] - vertice[i],
                    vertice[(j + 1) % sz] - vertice[j]) >= 0 ?
            j :
            i)) %= sz;
      ret = std::max(ret, sqr_dist_PP(vertice[i], vertice[j]));
    } while (i != is || j != js);
    return ret;
  })
#undef SCALA_FUNC
#define SELF_FUNC(name, func_body) \
  self &do_##name() func_body;     \
  friend self name(self lhs) { return lhs.do_##name(); }
  SELF_FUNC(convex_hull, {
    ptrdiff_t sz = vertice.size();
    if (sz <= 1) return *this;
    resort();
    cont_t<point_t> cvh(sz * 2);
    ptrdiff_t sz_cvh = 0;
    for (ptrdiff_t i = 0; i < sz; cvh[sz_cvh++] = vertice[i++])
      while (sz_cvh > 1 &&
             cross_sign(cvh[sz_cvh - 2], cvh[sz_cvh - 1], vertice[i]) <= 0)
        --sz_cvh;
    for (ptrdiff_t i = sz - 2, t = sz_cvh; ~i; cvh[sz_cvh++] = vertice[i--])
      while (sz_cvh > t &&
             cross_sign(cvh[sz_cvh - 2], cvh[sz_cvh - 1], vertice[i]) <= 0)
        --sz_cvh;
    cvh.resize(sz_cvh - 1);
    vertice = cvh;
    return *this;
  })
  SELF_FUNC(convex_hull_nonstrict, {
    reunique();
    ptrdiff_t sz = vertice.size();
    if (sz <= 1) return *this;
    cont_t<point_t> cvh(sz * 2);
    ptrdiff_t sz_cvh = 0;
    for (ptrdiff_t i = 0; i < sz; cvh[sz_cvh++] = vertice[i++])
      while (sz_cvh > 1 &&
             cross_sign(cvh[sz_cvh - 2], cvh[sz_cvh - 1], vertice[i]) < 0)
        --sz_cvh;
    for (ptrdiff_t i = sz - 2, t = sz_cvh; ~i; cvh[sz_cvh++] = vertice[i--])
      while (sz_cvh > t &&
             cross_sign(cvh[sz_cvh - 2], cvh[sz_cvh - 1], vertice[i]) < 0)
        --sz_cvh;
    cvh.resize(sz_cvh - 1);
    vertice = cvh;
    return *this;
  })
#undef SELF_FUNC
};
}  // namespace calc_geo
using namespace calc_geo;
auto solve([[maybe_unused]] int t_) -> void {
  read_var_(int, n);
  read_container_(vc<Point2>, v, n);
  cout << fixed << setprecision(0)
       << Polynomial2(v).do_convex_hull().convex_diameter();
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
