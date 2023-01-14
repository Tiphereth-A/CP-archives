#include <bits/extc++.h>
using namespace std;
template <typename Tp>
using vc = std::vector<Tp>;
#define foreach_ref_(i, container) for (auto &i : (container))
#define all_(a) (a).begin(), (a).end()
#define read_container_(type, name, size) \
  type name(size);                        \
  foreach_ref_(i, name) std::cin >> i;
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
namespace calc_geo {
using data_t = double;
template <typename Tp>
using cont_t = std::vector<Tp>;
const data_t EPS = 1e-9;
const data_t DATA_MAX = DBL_MAX;
ptrdiff_t sign(data_t lhs) { return lhs < -EPS ? -1 : lhs > EPS; }
bool is_negative(data_t x) { return sign(x) & 2; }
bool is_zero(data_t x) { return !sign(x); }
bool is_positive(data_t x) { return (sign(x) + 1) & 2; }
ptrdiff_t comp(data_t lhs, data_t rhs) { return sign(lhs - rhs); }
bool is_less(data_t lhs, data_t rhs) { return is_negative(lhs - rhs); }
bool is_equal(data_t lhs, data_t rhs) { return is_zero(lhs - rhs); }
bool is_greater(data_t lhs, data_t rhs) { return is_positive(lhs - rhs); }
bool is_intersect(data_t l1, data_t r1, data_t l2, data_t r2) {
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
bool is_in_middle(data_t l, data_t mid, data_t r) {
  return is_equal(l, mid) || is_equal(r, mid) || ((l < mid) ^ (r < mid));
}
struct Point2 {
  using self = Point2;
  data_t x, y;
  Point2(data_t x = data_t{}, data_t y = data_t{}): x(x), y(y) {}
  friend istream &operator>>(istream &is, self &rhs) {
    return is >> rhs.x >> rhs.y;
  }
  friend ostream &operator<<(ostream &os, const self &rhs) {
    return os << rhs.x << ' ' << rhs.y;
  }
  self &set_as_polar(data_t r, data_t theta) {
    return *this = {r * cos(theta), r * sin(theta)};
  }
  friend self lerp(const self &lhs, const self &rhs, data_t coord) {
    return lhs * coord + rhs * (1 - coord);
  }
  friend self mid_point(const self &lhs, const self &rhs) {
    return lerp(lhs, rhs, 0.5);
  }
#define SCALA_OP(op)               \
  self &operator op##=(data_t n) { \
    this->x op## = n;              \
    this->y op## = n;              \
    return *this;                  \
  }                                \
  self operator op(data_t n) const { return self(*this) op## = n; }
  SCALA_OP(+)
  SCALA_OP(-)
  SCALA_OP(*)
  SCALA_OP(/)
#undef SCALA_OP
#define VEC_OP(op)                         \
  self &operator op##=(const self & rhs) { \
    this->x op## = rhs.x;                  \
    this->y op## = rhs.y;                  \
    return *this;                          \
  }                                        \
  self operator op(const self &rhs) const { return self(*this) op## = rhs; }
  VEC_OP(+)
  VEC_OP(-)
#undef VEC_OP
  self operator-() const { return self{-x, -y}; }
  bool operator<(const self &rhs) const {
    auto c = comp(x, rhs.x);
    if (c) return c >> 1;
    return comp(y, rhs.y) >> 1;
  }
  bool operator==(const self &rhs) const {
    return is_equal(x, rhs.x) && is_equal(y, rhs.y);
  }
  friend data_t dot_mul(const self &lhs, const self &rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
  }
  friend data_t cross_mul(const self &lhs, const self &rhs) {
    return lhs.x * rhs.y - lhs.y * rhs.x;
  }
#define SCALA_FUNC(name, func_body) \
  data_t name() const func_body;    \
  friend data_t name(const self &lhs) { return lhs.name(); }
  SCALA_FUNC(arg, { return atan2(y, x); })
  SCALA_FUNC(arg_2pi, {
    data_t tmp_ = arg();
    return is_negative(tmp_) ? tmp_ + 2 * acos(data_t{-1}) : tmp_;
  })
  SCALA_FUNC(norm, { return x * x + y * y; })
  SCALA_FUNC(abs, { return sqrt(norm()); })
  static constexpr int QUAD_STATE[3][3] = {{5, 6, 7}, {4, 0, 0}, {3, 2, 1}};
  int quad() const { return QUAD_STATE[sign(y) + 1][sign(x) + 1]; };
  friend data_t quad(const self &lhs) { return lhs.quad(); }
#undef SCALA_FUNC
#define SELF_FUNC(name, func_body) \
  self &do_##name() func_body;     \
  friend self name(self lhs) { return lhs.do_##name(); }
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
  self &do_rotate(data_t theta) {
    data_t _x = x, _y = y;
    x = _x * cos(theta) - _y * sin(theta);
    y = _x * sin(theta) + _y * cos(theta);
    return *this;
  };
  friend self rotate(self lhs, data_t theta) { return lhs.do_rotate(theta); }
};
data_t dist_PP(const Point2 &lhs, const Point2 &rhs) {
  return hypot(lhs.x - rhs.x, lhs.y - rhs.y);
}
data_t sqr_dist_PP(const Point2 &lhs, const Point2 &rhs) {
  return (lhs.x - rhs.x) * (lhs.x - rhs.x) + (lhs.y - rhs.y) * (lhs.y - rhs.y);
}
data_t cross(const Point2 &p1, const Point2 &p2, const Point2 &p3) {
  return (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
}
ptrdiff_t cross_sign(const Point2 &p1, const Point2 &p2, const Point2 &p3) {
  return sign(cross(p1, p2, p3));
}
data_t dot(const Point2 &p1, const Point2 &p2, const Point2 &p3) {
  return (p2.x - p1.x) * (p3.x - p1.x) + (p2.y - p1.y) * (p3.y - p1.y);
}
ptrdiff_t dot_sign(const Point2 &p1, const Point2 &p2, const Point2 &p3) {
  return sign(dot(p1, p2, p3));
}
bool is_in_middle(Point2 a, Point2 m, Point2 b) {
  return is_in_middle(a.x, m.x, b.x) && is_in_middle(a.y, m.y, b.y);
}
data_t ang_PP(const Point2 &p1, const Point2 &p2) {
  return atan2(cross_mul(p1, p2), dot_mul(p1, p2));
}
struct Triangle {
  using self = Triangle;
  using point_t = Point2;
  point_t A, B, C;
  Triangle(const point_t &a = point_t{},
           const point_t &b = point_t{},
           const point_t &c = point_t{})
    : A(a), B(b), C(c) {}
  Triangle(const data_t &a_x,
           const data_t &a_y,
           const data_t &b_x,
           const data_t &b_y,
           const data_t &c_x,
           const data_t &c_y)
    : A(a_x, a_y), B(b_x, b_y), C(c_x, c_y) {}
  friend istream &operator>>(istream &is, self &rhs) {
    return is >> rhs.A >> rhs.B >> rhs.C;
  }
  friend ostream &operator<<(ostream &os, const self &rhs) {
    return os << rhs.A << ' ' << rhs.B << ' ' << rhs.C;
  }
  data_t area() const { return abs(cross(A, B, C)) / 2; }
  point_t average_w(data_t wA, data_t wB, data_t wC) const {
    return (A * wA + B * wB + C * wC) / (wA + wB + wC);
  }
  data_t radius_I() const {
    data_t ab = dist_PP(A, B), bc = dist_PP(B, C), ca = dist_PP(C, A);
    return 2 * area() / (ab + bc + ca);
  }
  data_t radius_O() const {
    data_t ab = dist_PP(A, B), bc = dist_PP(B, C), ca = dist_PP(C, A);
    return ab * bc * ca / (4 * area());
  }
  Point2 center_I() const {
    return average_w((B - C).abs(), (C - A).abs(), (A - B).abs());
  }
  Point2 center_E() const {
    return average_w(-((B - C).abs()), (C - A).abs(), (A - B).abs());
  }
  Point2 center_O() const {
    data_t a2 = (B - C).norm(), b2 = (C - A).norm(), c2 = (A - B).norm();
    return average_w(
      a2 * (b2 + c2 - a2), b2 * (c2 + a2 - b2), c2 * (a2 + b2 - c2));
  }
  Point2 center_G() const { return average_w(1, 1, 1); }
  Point2 center_H() const {
    data_t a2 = (B - C).norm(), b2 = (C - A).norm(), c2 = (A - B).norm();
    data_t a4 = a2 * a2, b4 = b2 * b2, c4 = c2 * c2;
    return average_w(a4 - b4 - c4 + 2 * b2 * c2,
                     b4 - c4 - a4 + 2 * c2 * a2,
                     c4 - a4 - b4 + 2 * a2 * b2);
  }
  Point2 center_N() const { return mid_point(center_O(), center_H()); }
  Point2 center_X() const {
    data_t s3 = sqrt(data_t{3}), r = radius_I(), R = radius_O(),
           s = ((A - B).abs() + (B - C).abs() + (C - A).abs()) / 2;
    return center_I() * (s3 * (r * r + 2 * r * R + s * s)) +
           center_O() * (-6 * r * (s3 * R - 2 * s)) +
           center_G() * (-2 * r * (s3 * r + 3 * s));
  }
};
struct Line2 {
  using self = Line2;
  using point_t = Point2;
  point_t l, r;
  Line2(const point_t &start_ = point_t{}, const point_t &end_ = point_t{})
    : l(start_), r(end_) {}
  Line2(const data_t &start_x,
        const data_t &start_y,
        const data_t &end_x,
        const data_t &end_y)
    : l(start_x, start_y), r(end_x, end_y) {}
  friend istream &operator>>(istream &is, self &rhs) {
    return is >> rhs.l >> rhs.r;
  }
  friend ostream &operator<<(ostream &os, const self &rhs) {
    return os << rhs.l << ' ' << rhs.r;
  }
  friend bool operator<(const self &lhs, const self &rhs) {
    if (is_same_dir(lhs, rhs)) return rhs.is_include(lhs.l);
    auto vl = lhs.direction();
    auto vr = rhs.direction();
    if (vl.quad() != vr.quad()) return vl.quad() < vr.quad();
    return is_positive(cross_mul(vl, vr));
  }
  data_t slope() const { return (r.y - l.y) / (r.x - l.x); }
  data_t slope_inv() const { return (r.x - l.x) / (r.y - l.y); }
  data_t intercept_v() const { return r.y - r.x * slope(); }
  data_t intercept_h() const { return r.x - r.y * slope_inv(); }
  data_t lerp_y(data_t x) const { return l.y + (x - l.x) * slope(); }
  data_t lerp_x(data_t y) const { return l.x + (y - l.y) * slope_inv(); }
  friend bool is_parallel(const self &lhs, const self &rhs) {
    return is_zero(cross_mul(lhs.direction(), rhs.direction()));
  }
  friend bool is_same_dir(const self &lhs, const self &rhs) {
    return is_parallel(lhs, rhs) &&
           is_positive(dot_mul(lhs.direction(), rhs.direction()));
  }
  point_t direction() const { return r - l; }
  bool is_include(const point_t &p) const {
    return is_positive(cross(l, r, p));
  }
  self &do_push(data_t eps = 1e-8) {
    point_t delta = direction().do_rotate90().do_unit();
    delta *= eps;
    l += delta;
    r += delta;
    return *this;
  }
  friend self push(self line, data_t eps = 1e-8) { return line.do_push(eps); }
};
bool is_ins_LL(const Line2 &l1, const Line2 &l2) {
  return !is_zero(cross(l2.l, l2.r, l1.l) - cross(l2.l, l2.r, l1.r));
}
Point2 ins_LL(const Line2 &l1, const Line2 &l2) {
  data_t a1 = cross(l2.l, l2.r, l1.l), a2 = -cross(l2.l, l2.r, l1.r);
  return (l1.l * a2 + l1.r * a1) / (a1 + a2);
}
bool is_ins_SS(const Line2 &l1, const Line2 &l2) {
  return is_intersect(l1.l.x, l1.r.x, l2.l.x, l2.r.x) &&
         is_intersect(l1.l.y, l1.r.y, l2.l.y, l2.r.y) &&
         cross_sign(l1.l, l1.r, l2.l) * cross_sign(l1.l, l1.r, l2.r) <= 0 &&
         cross_sign(l2.l, l2.r, l1.l) * cross_sign(l2.l, l2.r, l1.r) <= 0;
}
bool is_ins_SS_strict(const Line2 &s1, const Line2 &s2) {
  return cross_sign(s1.l, s1.r, s2.l) * cross_sign(s1.l, s1.r, s2.r) < 0 &&
         cross_sign(s2.l, s2.r, s1.l) * cross_sign(s2.l, s2.r, s1.r) < 0;
}
Point2 proj(const Line2 &l1, const Point2 &p) {
  Point2 dir = l1.direction();
  return l1.l + dir * (dot_mul(dir, p - l1.l) / dir.norm());
}
Point2 reflect(const Line2 &l1, const Point2 &p) { return proj(l1, p) * 2 - p; }
bool is_on_S(const Line2 &s1, const Point2 &p) {
  return is_zero(cross(s1.l, s1.r, p)) && is_in_middle(s1.l, p, s1.r);
}
bool is_on_S_strict(const Line2 &s1, const Point2 &p) {
  return cross_sign(s1.l, s1.r, p) == 0 &&
         sign(dot_mul(p - s1.l, s1.l - s1.r)) *
             sign(dot_mul(p - s1.r, s1.l - s1.r)) <
           0;
}
data_t dist_PPS(const Line2 &s1, const Point2 &p) {
  if (s1.l == s1.r) return dist_PP(s1.l, p);
  Point2 h = proj(s1, p);
  if (is_in_middle(s1.l, h, s1.r)) return dist_PP(p, h);
  return min(dist_PP(s1.l, p), dist_PP(s1.r, p));
}
data_t dist_SS(const Line2 &s1, const Line2 &s2) {
  if (is_ins_SS(s1, s2)) return 0;
  return min({dist_PPS(s1, s2.l),
              dist_PPS(s1, s2.r),
              dist_PPS(s2, s1.l),
              dist_PPS(s2, s1.r)});
}
struct Polynomial2 {
  using self = Polynomial2;
  using point_t = Point2;
  cont_t<point_t> vertice;
  explicit Polynomial2(size_t size_): vertice(size_) {}
  Polynomial2(const cont_t<point_t> &vertice_): vertice(vertice_) {}
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
  data_t name() const func_body;    \
  friend data_t name(const self &lhs) { return lhs.name(); }
  SCALA_FUNC(circum, {
    data_t result{};
    size_t sz = vertice.size();
    for (size_t i = 0; i < sz; ++i)
      result += dist_PP(vertice[i], vertice[(i + 1) % sz]);
    return result;
  })
  SCALA_FUNC(area, {
    data_t result{};
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
    data_t ret = dist_PP(vertice[i], vertice[j]);
    do {
      (++(cross_mul(vertice[(i + 1) % sz] - vertice[i],
                    vertice[(j + 1) % sz] - vertice[j]) >= 0 ?
            j :
            i)) %= sz;
      ret = std::max(ret, dist_PP(vertice[i], vertice[j]));
    } while (i != is || j != js);
    return ret;
  })
#undef SCALA_FUNC
  static const size_t inside_or_onborder = 3;
  static const size_t inside = 2;
  static const size_t onborder = 1;
  static const size_t outside = 0;
  size_t is_containing(const point_t &p) const {
    bool result = 0;
    size_t sz = vertice.size();
    for (size_t i = 0; i < sz; ++i) {
      point_t now_p = vertice[i], next_p = vertice[(i + 1) % sz];
      if (is_on_S({now_p, next_p}, p)) return self::onborder;
      if (!is_greater(now_p.y, next_p.y)) std::swap(now_p, next_p);
      if (is_greater(p.y, now_p.y) || !is_greater(p.y, next_p.y)) continue;
      result ^= cross_sign(p, now_p, next_p) > 0;
    }
    return result ? self::inside : self::outside;
  }
  size_t is_containing_cvh(const point_t &p) const {
    if (is_positive(cross(vertice.front(), p, vertice[1])) ||
        is_positive(cross(vertice.front(), vertice.back(), p)))
      return self::outside;
    auto it =
      std::lower_bound(vertice.begin() + 1,
                       vertice.end(),
                       p,
                       [&](const point_t &lhs, const point_t &rhs) {
                         return is_positive(cross(vertice.front(), lhs, rhs));
                       }) -
      1;
    auto next_it = it + 1;
    if (next_it == vertice.end()) next_it = vertice.begin();
    auto res = cross_sign(p, *it, *next_it);
    if (res) return ~res ? self::inside_or_onborder : self::outside;
    return is_zero(res) && !is_positive(dot(p, *it, *next_it)) ?
             self::inside_or_onborder :
             self::outside;
  }
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
  self &do_minkowski_sum(const self &rhs) {
    size_t n = vertice.size(), m = rhs.vertice.size();
    if (!m) return *this;
    if (!n) return *this = rhs;
    cont_t<Point2> result;
    result.reserve(n + m);
    size_t midxl = 0;
    for (size_t i = 1; i < n; ++i)
      if (vertice[i] < vertice[midxl]) midxl = i;
    size_t midxr = 0;
    for (size_t i = 1; i < m; ++i)
      if (rhs[i] < rhs[midxr]) midxr = i;
    bool fl = false, fr = false;
    for (size_t idxl = midxl, idxr = midxr;
         !(idxl == midxl && fl) || !(idxr == midxr && fr);) {
      Point2 diffl = vertice[(idxl + 1) % n] - vertice[idxl];
      Point2 diffr = rhs[(idxr + 1) % m] - rhs[idxr];
      bool f = !(idxl == midxl && fl) &&
               ((idxr == midxr && fr) || is_positive(cross_mul(diffl, diffr)));
      result.push_back(vertice[idxl] + rhs[idxr] + (f ? diffl : diffr));
      (++(f ? idxl : idxr)) %= (f ? n : m);
      (f ? fl : fr) |= !(f ? idxl : idxr);
    }
    vertice = result;
    return *this;
  }
  friend self minkowski_sum(self poly, const self &rhs) {
    return poly.do_minkowski_sum(rhs);
  }
  self &do_convex_cut(const point_t &q1, const point_t &q2) {
    size_t sz = vertice.size();
    cont_t<point_t> cvc;
    for (size_t i = 0; i < sz; ++i) {
      point_t p1 = vertice[i], p2 = vertice[(i + 1) % sz];
      ptrdiff_t d1 = cross_sign(q1, q2, p1), d2 = cross_sign(q1, q2, p2);
      if (d1 >= 0) cvc.push_back(p1);
      if (d1 * d2 < 0) cvc.push_back(ins_LL({p1, p2}, {q1, q2}));
    }
    vertice = cvc;
    return *this;
  }
  friend self convex_cut(self poly, const point_t &q1, const point_t &q2) {
    return poly.do_convex_cut(q1, q2);
  }
};
data_t min_dist(const cont_t<Point2> &vp, ptrdiff_t l, ptrdiff_t r) {
  data_t ret = DATA_MAX;
  if (r - l <= 5) {
    for (ptrdiff_t i = l; i < r; ++i)
      for (ptrdiff_t j = l; j < i; ++j)
        ret = std::min(ret, dist_PP(vp[i], vp[j]));
    return ret;
  }
  ptrdiff_t mid = r - (r - l) / 2;
  ret = min(min_dist(vp, l, mid), min_dist(vp, mid, r));
  cont_t<Point2> q;
  for (ptrdiff_t i = l; i < r; ++i)
    if (std::abs(vp[i].x - vp[mid].x) <= ret) q.push_back(vp[i]);
  std::sort(
    q.begin(), q.end(), [](const Point2 &lhs, const Point2 &rhs) -> bool {
      return lhs.y < rhs.y;
    });
  for (ptrdiff_t i = 1; i < (ptrdiff_t)q.size(); ++i)
    for (ptrdiff_t j = i - 1; ~j && q[j].y >= q[i].y - ret; --j)
      ret = std::min(ret, dist_PP(q[i], q[j]));
  return ret;
}
Polynomial2 ins_hP(cont_t<Line2> vl) {
  auto check = [](const Line2 &u, const Line2 &v, const Line2 &w) -> bool {
    return w.is_include(ins_LL(u, v));
  };
  std::sort(vl.begin(), vl.end());
  deque<Line2> q;
  for (auto it = vl.begin(); it != vl.end(); ++it) {
    if (it != vl.begin() && is_same_dir(*it, *(it - 1))) continue;
    while (q.size() > 1 && !check(*(q.rbegin() + 1), q.back(), *it))
      q.pop_back();
    while (q.size() > 1 && !check(*(q.begin() + 1), q.front(), *it))
      q.pop_front();
    q.push_back(*it);
  }
  while (q.size() > 2 && !check(*(q.rbegin() + 1), q.back(), q.front()))
    q.pop_back();
  while (q.size() > 2 && !check(*(q.begin() + 1), q.front(), q.back()))
    q.pop_front();
  cont_t<Point2> ret;
  for (size_t i = 0; i < q.size(); ++i)
    ret.push_back(ins_LL(q[i], q[(i + 1) % q.size()]));
  return ret;
}
}  // namespace calc_geo
using namespace calc_geo;
auto solve([[maybe_unused]] int t_) -> void {
  int l, s;
  while (cin >> l) {
    read_container_(vc<Point2>, vpl, l);
    cin >> s;
    read_container_(vc<Point2>, vps, s);
    Polynomial2 poly{vpl};
    poly.do_convex_hull();
    cout << count_if(all_(vps), [&poly](const Point2 &p) -> bool {
      return poly.is_containing_cvh(p);
    }) << '\n';
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int i_ = 0;
  cout << fixed << setprecision(0);
  solve(i_);
  return 0;
}
