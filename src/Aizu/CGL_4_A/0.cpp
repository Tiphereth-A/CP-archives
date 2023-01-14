#include <bits/stdc++.h>
using namespace std;
#define for_(i, l, r, vars...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vars; i <= i##end; ++i)
#define read_var_(type, name) \
  type name;                  \
  std::cin >> name
template <class Tp>
auto chkmin(Tp &a, Tp b) -> bool {
  return b < a ? a = b, true : false;
};
template <class Tp>
auto chkmax(Tp &a, Tp b) -> bool {
  return a < b ? a = b, true : false;
};
namespace geometry2d {
using data_t = double;
template <typename Tp>
using cont_t = std::vector<Tp>;
constexpr data_t EPS = 1e-8;
constexpr data_t DATA_MAX = std::numeric_limits<data_t>::max();
constexpr ptrdiff_t sign(data_t lhs) { return lhs < -EPS ? -1 : lhs > EPS; }
constexpr bool is_negative(data_t x) { return sign(x) & 2; }
constexpr bool is_zero(data_t x) { return !sign(x); }
constexpr bool is_positive(data_t x) { return (sign(x) + 1) & 2; }
constexpr ptrdiff_t comp(data_t lhs, data_t rhs) { return sign(lhs - rhs); }
constexpr bool is_less(data_t lhs, data_t rhs) {
  return is_negative(lhs - rhs);
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
  data_t x, y;
  constexpr Point2(data_t x = data_t{}, data_t y = data_t{}): x(x), y(y) {}
  friend std::istream &operator>>(std::istream &is, Point2 &rhs) {
    return is >> rhs.x >> rhs.y;
  }
  friend std::ostream &operator<<(std::ostream &os, const Point2 &rhs) {
    return os << rhs.x << ' ' << rhs.y;
  }
  constexpr Point2 &set_as_polar(data_t r, data_t theta) {
    return *this = {r * cos(theta), r * sin(theta)};
  }
  friend constexpr Point2
  lerp(const Point2 &lhs, const Point2 &rhs, data_t coord) {
    return lhs * coord + rhs * (1 - coord);
  }
  friend constexpr Point2 mid_point(const Point2 &lhs, const Point2 &rhs) {
    return lerp(lhs, rhs, 0.5);
  }
#define SCALA_OP(op)                             \
  constexpr Point2 &operator op##=(data_t n) {   \
    this->x op## = n;                            \
    this->y op## = n;                            \
    return *this;                                \
  }                                              \
  constexpr Point2 operator op(data_t n) const { \
    return Point2(*this) op## = n;               \
  }
  SCALA_OP(+)
  SCALA_OP(-)
  SCALA_OP(*)
  SCALA_OP(/)
#undef SCALA_OP
#define VEC_OP(op)                                        \
  constexpr Point2 &operator op##=(const Point2 & rhs) {  \
    this->x op## = rhs.x;                                 \
    this->y op## = rhs.y;                                 \
    return *this;                                         \
  }                                                       \
  constexpr Point2 operator op(const Point2 &rhs) const { \
    return Point2(*this) op## = rhs;                      \
  }
  VEC_OP(+)
  VEC_OP(-)
#undef VEC_OP
  constexpr Point2 operator-() const { return Point2{-x, -y}; }
  constexpr bool operator<(const Point2 &rhs) const {
    auto c = comp(x, rhs.x);
    if (c) return c >> 1;
    return comp(y, rhs.y) >> 1;
  }
  constexpr bool operator==(const Point2 &rhs) const {
    return is_equal(x, rhs.x) && is_equal(y, rhs.y);
  }
  constexpr bool operator!=(const Point2 &rhs) const { return !(*this == rhs); }
  friend constexpr data_t dot_mul(const Point2 &lhs, const Point2 &rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
  }
  friend constexpr data_t cross_mul(const Point2 &lhs, const Point2 &rhs) {
    return lhs.x * rhs.y - lhs.y * rhs.x;
  }
#define SCALA_FUNC(name, func_body)      \
  constexpr auto name() const func_body; \
  friend constexpr auto name(const Point2 &lhs) { return lhs.name(); }
  SCALA_FUNC(arg, { return atan2(y, x); })
  SCALA_FUNC(arg_2pi, {
    data_t tmp_ = arg();
    return is_negative(tmp_) ? tmp_ + 2 * acos(data_t{-1}) : tmp_;
  })
  SCALA_FUNC(norm, { return x * x + y * y; })
  SCALA_FUNC(abs, { return sqrt(norm()); })
  static constexpr int QUAD_STATE[3][3] = {{5, 6, 7}, {4, 0, 0}, {3, 2, 1}};
  SCALA_FUNC(quad, { return QUAD_STATE[sign(y) + 1][sign(x) + 1]; })
#undef SCALA_FUNC
#define SELF_FUNC(name, func_body)         \
  constexpr Point2 &do_##name() func_body; \
  friend constexpr Point2 name(Point2 lhs) { return lhs.do_##name(); }
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
  constexpr Point2 &do_rotate(data_t theta) {
    data_t _x = x, _y = y;
    x = _x * cos(theta) - _y * sin(theta);
    y = _x * sin(theta) + _y * cos(theta);
    return *this;
  };
  friend constexpr Point2 rotate(Point2 lhs, data_t theta) {
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
constexpr data_t dot(const Point2 &p1, const Point2 &p2, const Point2 &p3) {
  return (p2.x - p1.x) * (p3.x - p1.x) + (p2.y - p1.y) * (p3.y - p1.y);
}
constexpr ptrdiff_t
dot_sign(const Point2 &p1, const Point2 &p2, const Point2 &p3) {
  return sign(dot(p1, p2, p3));
}
constexpr bool is_in_middle(Point2 a, Point2 m, Point2 b) {
  return is_in_middle(a.x, m.x, b.x) && is_in_middle(a.y, m.y, b.y);
}
constexpr data_t ang_PP(const Point2 &p1, const Point2 &p2) {
  return atan2(cross_mul(p1, p2), dot_mul(p1, p2));
}
struct Line2 {
  Point2 l, r;
  Line2() = default;
  constexpr Line2(const Point2 &start_, const Point2 &end_)
    : l(start_), r(end_) {}
  constexpr Line2(const data_t &start_x,
                  const data_t &start_y,
                  const data_t &end_x,
                  const data_t &end_y)
    : l(start_x, start_y), r(end_x, end_y) {}
  friend std::istream &operator>>(std::istream &is, Line2 &rhs) {
    return is >> rhs.l >> rhs.r;
  }
  friend std::ostream &operator<<(std::ostream &os, const Line2 &rhs) {
    return os << rhs.l << ' ' << rhs.r;
  }
  constexpr friend bool operator<(const Line2 &lhs, const Line2 &rhs) {
    if (is_same_dir(lhs, rhs)) return rhs.is_include(lhs.l);
    auto vl = lhs.direction();
    auto vr = rhs.direction();
    if (vl.quad() != vr.quad()) return vl.quad() < vr.quad();
    return is_positive(cross_mul(vl, vr));
  }
  friend constexpr bool is_parallel(const Line2 &lhs, const Line2 &rhs) {
    return is_zero(cross_mul(lhs.direction(), rhs.direction()));
  }
  friend constexpr bool is_same_dir(const Line2 &lhs, const Line2 &rhs) {
    return is_parallel(lhs, rhs) &&
           is_positive(dot_mul(lhs.direction(), rhs.direction()));
  }
  constexpr Point2 direction() const { return r - l; }
  constexpr bool is_include(const Point2 &p) const {
    return is_positive(cross(l, r, p));
  }
  constexpr bool passes_through(const Point2 &p) const {
    return is_zero(cross(l, r, p));
  }
  constexpr Line2 &do_push(data_t eps = 1e-8) {
    Point2 delta = direction().do_rotate90().do_unit();
    delta *= eps;
    l += delta;
    r += delta;
    return *this;
  }
  friend constexpr Line2 push(Line2 line, data_t eps = 1e-8) {
    return line.do_push(eps);
  }
};
constexpr bool is_ins_LL(const Line2 &l1, const Line2 &l2) {
  return !is_zero(cross(l2.l, l2.r, l1.l) - cross(l2.l, l2.r, l1.r));
}
constexpr Point2 ins_LL(const Line2 &l1, const Line2 &l2) {
  data_t a1 = cross(l2.l, l2.r, l1.l), a2 = -cross(l2.l, l2.r, l1.r);
  return (l1.l * a2 + l1.r * a1) / (a1 + a2);
}
constexpr bool is_ins_SS(const Line2 &l1, const Line2 &l2) {
  return is_intersect(l1.l.x, l1.r.x, l2.l.x, l2.r.x) &&
         is_intersect(l1.l.y, l1.r.y, l2.l.y, l2.r.y) &&
         cross_sign(l1.l, l1.r, l2.l) * cross_sign(l1.l, l1.r, l2.r) <= 0 &&
         cross_sign(l2.l, l2.r, l1.l) * cross_sign(l2.l, l2.r, l1.r) <= 0;
}
constexpr bool is_ins_SS_strict(const Line2 &s1, const Line2 &s2) {
  return cross_sign(s1.l, s1.r, s2.l) * cross_sign(s1.l, s1.r, s2.r) < 0 &&
         cross_sign(s2.l, s2.r, s1.l) * cross_sign(s2.l, s2.r, s1.r) < 0;
}
constexpr Point2 proj(const Line2 &l1, const Point2 &p) {
  Point2 dir = l1.direction();
  return l1.l + dir * (dot_mul(dir, p - l1.l) / dir.norm());
}
constexpr Point2 reflect(const Line2 &l1, const Point2 &p) {
  return proj(l1, p) * 2 - p;
}
constexpr bool
is_on_same_L(const Point2 &p1, const Point2 &p2, const Point2 &p3) {
  return is_zero(cross(p1, p2, p3));
}
constexpr bool is_on_S(const Line2 &s1, const Point2 &p) {
  return is_on_same_L(s1.l, s1.r, p) && is_in_middle(s1.l, p, s1.r);
}
constexpr bool is_on_S_strict(const Line2 &s1, const Point2 &p) {
  return cross_sign(s1.l, s1.r, p) == 0 &&
         sign(dot_mul(p - s1.l, s1.l - s1.r)) *
             sign(dot_mul(p - s1.r, s1.l - s1.r)) <
           0;
}
constexpr data_t dist_PL(const Point2 &p, const Line2 &s1) {
  if (s1.l == s1.r) return dist_PP(s1.l, p);
  return dist_PP(p, proj(s1, p));
}
constexpr data_t dist_PS(const Point2 &p, const Line2 &s1) {
  if (s1.l == s1.r) return dist_PP(s1.l, p);
  Point2 h = proj(s1, p);
  if (is_in_middle(s1.l, h, s1.r)) return dist_PP(p, h);
  return std::min(dist_PP(s1.l, p), dist_PP(s1.r, p));
}
constexpr data_t dist_SS(const Line2 &s1, const Line2 &s2) {
  if (is_ins_SS(s1, s2)) return 0;
  return std::min({dist_PS(s1.l, s2),
                   dist_PS(s1.r, s2),
                   dist_PS(s2.l, s1),
                   dist_PS(s2.r, s1)});
}
struct Polynomial2 {
  cont_t<Point2> vs;
  Polynomial2() = default;
  explicit Polynomial2(size_t size_): vs(size_) {}
  explicit Polynomial2(const cont_t<Point2> &vs_): vs(vs_) {}
  friend std::istream &operator>>(std::istream &is, Polynomial2 &rhs) {
    for (auto &i : rhs.vs) is >> i;
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const Polynomial2 &rhs) {
    for (auto it = rhs.vs.begin(); it != rhs.vs.end() - 1; ++it)
      os << *it << ' ';
    return os << rhs.vs.back();
  }
  Polynomial2 &resort() {
    std::sort(vs.begin(), vs.end());
    return *this;
  }
  Polynomial2 &reunique() {
    resort();
    vs.erase(std::unique(vs.begin(), vs.end()), vs.end());
    return *this;
  }
  Point2 &operator[](size_t x) { return vs[x]; }
  const Point2 &operator[](size_t x) const { return vs[x]; }
  cont_t<Point2>::iterator prev(cont_t<Point2>::iterator it) {
    if (it == vs.begin()) it = vs.end();
    return --it;
  }
  cont_t<Point2>::const_iterator prev(cont_t<Point2>::const_iterator it) const {
    if (it == vs.begin()) it = vs.end();
    return --it;
  }
  cont_t<Point2>::iterator next(cont_t<Point2>::iterator it) {
    if (++it == vs.end()) it = vs.begin();
    return it;
  }
  cont_t<Point2>::const_iterator next(cont_t<Point2>::const_iterator it) const {
    if (++it == vs.end()) it = vs.begin();
    return it;
  }
  size_t prev(size_t idx) const { return (idx + vs.size() - 1) % vs.size(); }
  size_t next(size_t idx) const { return (idx + 1) % vs.size(); }
#define SCALA_FUNC(name, func_body) \
  auto name() const func_body;      \
  friend auto name(const Polynomial2 &lhs) { return lhs.name(); }
  SCALA_FUNC(circum, {
    data_t result{};
    for (size_t i = 0; i < vs.size(); ++i)
      result += dist_PP(vs[i], vs[next(i)]);
    return result;
  })
  SCALA_FUNC(area, {
    data_t result{};
    for (size_t i = 0; i < vs.size(); ++i)
      result += cross_mul(vs[i], vs[next(i)]);
    return result / 2;
  })
#undef SCALA_FUNC
  static constexpr size_t inside = 3;
  static constexpr size_t onendpoint = 2;
  static constexpr size_t onborder = 1;
  static constexpr size_t outside = 0;
  virtual size_t relation_P(const Point2 &p) const {
    for (auto &&now : vs)
      if (now == p) return onendpoint;
    bool result = false;
    for (size_t i = 0; i < vs.size(); ++i) {
      Point2 now_p = vs[i], next_p = vs[next(i)];
      if (is_on_S({now_p, next_p}, p)) return onborder;
      if (!is_greater(now_p.y, next_p.y)) std::swap(now_p, next_p);
      if (is_greater(p.y, now_p.y) || !is_greater(p.y, next_p.y)) continue;
      result ^= cross_sign(p, now_p, next_p) > 0;
    }
    return result ? inside : outside;
  }
  bool is_convex() const {
    bool flag[2] = {false, false};
    size_t sz = vs.size();
    if (sz < 3) return true;
    for (size_t i = 0, j = next(i), k = next(j); i < sz;
         ++i, j = next(j), k = next(k)) {
      auto sgn = cross_sign(vs[i], vs[j], vs[k]);
      if (sgn) flag[(sgn + 1) / 2] = true;
      if (flag[0] && flag[1]) return false;
    }
    return true;
  }
  Point2 mass_point() const {
    Point2 ret{};
    data_t area{};
    if (vs.size() == 0) return ret;
    if (vs.size() == 1) return vs[0];
    for (size_t i = 1; i < vs.size() - 1; ++i) {
      data_t tmp = cross(vs[0], vs[i], vs[i + 1]);
      if (is_zero(tmp)) continue;
      area += tmp;
      ret += (vs[0] + vs[i] + vs[i + 1]) * (tmp / 3);
    }
    if (!is_zero(area)) ret = ret / area;
    return ret;
  }
};
struct ConvexHull2: public Polynomial2 {
  ConvexHull2() = default;
  explicit ConvexHull2(size_t size_): Polynomial2(size_) {}
  explicit ConvexHull2(const cont_t<Point2> &vs_,
                       bool inited = false,
                       bool strict = true)
    : Polynomial2(vs_) {
    if (!inited) strict ? init() : init_nonstrict();
  }
  friend std::istream &operator>>(std::istream &is, ConvexHull2 &rhs) {
    for (auto &i : rhs.vs) is >> i;
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const ConvexHull2 &rhs) {
    for (auto it = rhs.vs.begin(); it != rhs.vs.end() - 1; ++it)
      os << *it << ' ';
    return os << rhs.vs.back();
  }
  ConvexHull2 &init() {
    ptrdiff_t sz = vs.size();
    if (sz <= 1) return *this;
    resort();
    cont_t<Point2> cvh(sz * 2);
    ptrdiff_t sz_cvh = 0;
    for (ptrdiff_t i = 0; i < sz; cvh[sz_cvh++] = vs[i++])
      while (sz_cvh > 1 &&
             cross_sign(cvh[sz_cvh - 2], cvh[sz_cvh - 1], vs[i]) <= 0)
        --sz_cvh;
    for (ptrdiff_t i = sz - 2, t = sz_cvh; ~i; cvh[sz_cvh++] = vs[i--])
      while (sz_cvh > t &&
             cross_sign(cvh[sz_cvh - 2], cvh[sz_cvh - 1], vs[i]) <= 0)
        --sz_cvh;
    cvh.resize(sz_cvh - 1);
    vs = cvh;
    return *this;
  }
  ConvexHull2 &init_nonstrict() {
    reunique();
    ptrdiff_t sz = vs.size();
    if (sz <= 1) return *this;
    cont_t<Point2> cvh(sz * 2);
    ptrdiff_t sz_cvh = 0;
    for (ptrdiff_t i = 0; i < sz; cvh[sz_cvh++] = vs[i++])
      while (sz_cvh > 1 &&
             cross_sign(cvh[sz_cvh - 2], cvh[sz_cvh - 1], vs[i]) < 0)
        --sz_cvh;
    for (ptrdiff_t i = sz - 2, t = sz_cvh; ~i; cvh[sz_cvh++] = vs[i--])
      while (sz_cvh > t &&
             cross_sign(cvh[sz_cvh - 2], cvh[sz_cvh - 1], vs[i]) < 0)
        --sz_cvh;
    cvh.resize(sz_cvh - 1);
    vs = cvh;
    return *this;
  }
  size_t relation_P(const Point2 &p) const override {
    for (auto &&now : vs)
      if (now == p) return onendpoint;
    size_t sz = vs.size();
    for (size_t i = 0; i < sz; ++i)
      if (is_on_S({vs[i], vs[next(i)]}, p)) return onborder;
    if (sz < 3) return outside;
    if (is_positive(cross(vs.front(), p, vs[1])) ||
        is_positive(cross(vs.front(), vs.back(), p)))
      return outside;
    auto it =
      std::lower_bound(vs.begin() + 1,
                       vs.end(),
                       p,
                       [&](const Point2 &lhs, const Point2 &rhs) {
                         return is_positive(cross(vs.front(), lhs, rhs));
                       }) -
      1;
    auto next_it = next(it);
    auto res = cross_sign(p, *it, *next_it);
    if (res) return ~res ? inside : outside;
    return !res && !is_positive(dot(p, *it, *next_it)) ? inside : outside;
  }
  friend bool is_ins_cvh(const ConvexHull2 &cvhl, const ConvexHull2 &cvhr) {
    for (auto &&now : cvhl.vs)
      if (cvhr.relation_P(now)) return false;
    for (auto &&now : cvhr.vs)
      if (cvhl.relation_P(now)) return false;
    size_t n = cvhl.vs.size(), m = cvhr.vs.size();
    if (n > 1 && m > 1) {
      for (size_t l = 0, nextl = 1; l < n; nextl = cvhl.next(l = nextl))
        for (size_t r = 0, nextr = 1; r < m; nextr = cvhl.next(r = nextr))
          if (is_ins_SS({cvhl[l], cvhl[nextl]}, {cvhr[r], cvhr[nextr]}))
            return false;
    } else if (n == 1) {
      if (cvhl[0] == cvhr[0]) return false;
      if (m == 1) return true;
      return !is_on_S({cvhr[0], cvhr[1]}, cvhl[0]);
    } else {
      if (is_on_S({cvhl[0], cvhl[1]}, cvhr[0])) return false;
      if (m == 1) return true;
      return !is_ins_SS({cvhl[0], cvhl[1]}, {cvhr[0], cvhr[1]});
    }
    return true;
  }
  data_t convex_diameter() const {
    size_t sz = vs.size();
    if (sz <= 1) return data_t{};
    size_t is = 0;
    size_t js = 0;
    for (size_t k = 1; k < sz; ++k) {
      is = vs[k] < vs[is] ? k : is;
      js = vs[js] < vs[k] ? k : js;
    }
    size_t i = is;
    size_t j = js;
    data_t ret = dist_PP(vs[i], vs[j]);
    do {
      (++(cross_mul(vs[next(i)] - vs[i], vs[next(j)] - vs[j]) >= 0 ? j : i)) %=
        sz;
      ret = std::max(ret, dist_PP(vs[i], vs[j]));
    } while (i != is || j != js);
    return ret;
  }
  friend Polynomial2 coverage_rect_with_min_area(ConvexHull2 &lhs) {
    size_t sz = lhs.vs.size();
    if (sz == 0) return lhs;
    if (sz == 1)
      return Polynomial2{cont_t<Point2>{lhs[0], lhs[0], lhs[0], lhs[0]}};
    if (sz == 2)
      return Polynomial2{cont_t<Point2>{lhs[0], lhs[0], lhs[1], lhs[1]}};
    lhs.vs.push_back(lhs.vs[0]);
    data_t ans = DATA_MAX;
    size_t r = 1, p = 1, q;
    size_t ans_i, ans_r, ans_p, ans_q;
    for (size_t i = 0; i < sz; ++i) {
      while (!is_negative(cross(lhs.vs[i], lhs.vs[i + 1], lhs.vs[r + 1]) -
                          cross(lhs.vs[i], lhs.vs[i + 1], lhs.vs[r])))
        r = (r + 1) % sz;
      while (!is_negative(dot(lhs.vs[i], lhs.vs[i + 1], lhs.vs[p + 1]) -
                          dot(lhs.vs[i], lhs.vs[i + 1], lhs.vs[p])))
        p = (p + 1) % sz;
      if (i == 0) q = p;
      while (!is_positive(dot(lhs.vs[i], lhs.vs[i + 1], lhs.vs[q + 1]) -
                          dot(lhs.vs[i], lhs.vs[i + 1], lhs.vs[q])))
        q = (q + 1) % sz;
      data_t tmp = cross(lhs.vs[i], lhs.vs[i + 1], lhs.vs[r]) *
                   (dot(lhs.vs[i], lhs.vs[i + 1], lhs.vs[p]) -
                    dot(lhs.vs[i], lhs.vs[i + 1], lhs.vs[q])) /
                   (lhs.vs[i] - lhs.vs[i + 1]).norm();
      if (ans > tmp) {
        ans = tmp;
        ans_i = i;
        ans_r = r;
        ans_p = p;
        ans_q = q;
      }
    }
    Point2 dir = Line2{lhs[ans_i], lhs[ans_i + 1]}.direction(),
           vdir = rotate90(dir);
    Polynomial2 ret{cont_t<Point2>{
      ins_LL({lhs[ans_i], lhs[ans_i] + dir}, {lhs[ans_p], lhs[ans_p] + vdir}),
      ins_LL({lhs[ans_i], lhs[ans_i] + dir}, {lhs[ans_q], lhs[ans_q] + vdir}),
      ins_LL({lhs[ans_r], lhs[ans_r] + dir}, {lhs[ans_p], lhs[ans_p] + vdir}),
      ins_LL({lhs[ans_r], lhs[ans_r] + dir}, {lhs[ans_q], lhs[ans_q] + vdir})}};
    lhs.vs.pop_back();
    return ret;
  }
  friend Polynomial2 coverage_rect_with_min_circum(ConvexHull2 &lhs) {
    size_t sz = lhs.vs.size();
    if (sz == 0) return lhs;
    if (sz == 1)
      return Polynomial2{cont_t<Point2>{lhs[0], lhs[0], lhs[0], lhs[0]}};
    if (sz == 2)
      return Polynomial2{cont_t<Point2>{lhs[0], lhs[0], lhs[1], lhs[1]}};
    lhs.vs.push_back(lhs.vs[0]);
    data_t ans = DATA_MAX;
    size_t r = 1, p = 1, q;
    size_t ans_i, ans_r, ans_p, ans_q;
    for (size_t i = 0; i < sz; ++i) {
      while (!is_negative(cross(lhs.vs[i], lhs.vs[i + 1], lhs.vs[r + 1]) -
                          cross(lhs.vs[i], lhs.vs[i + 1], lhs.vs[r])))
        r = (r + 1) % sz;
      while (!is_negative(dot(lhs.vs[i], lhs.vs[i + 1], lhs.vs[p + 1]) -
                          dot(lhs.vs[i], lhs.vs[i + 1], lhs.vs[p])))
        p = (p + 1) % sz;
      if (i == 0) q = p;
      while (!is_positive(dot(lhs.vs[i], lhs.vs[i + 1], lhs.vs[q + 1]) -
                          dot(lhs.vs[i], lhs.vs[i + 1], lhs.vs[q])))
        q = (q + 1) % sz;
      data_t tmp = (cross(lhs.vs[i], lhs.vs[i + 1], lhs.vs[r]) +
                    (dot(lhs.vs[i], lhs.vs[i + 1], lhs.vs[p]) -
                     dot(lhs.vs[i], lhs.vs[i + 1], lhs.vs[q]))) /
                   (lhs.vs[i] - lhs.vs[i + 1]).abs();
      if (ans > tmp) {
        ans = tmp;
        ans_i = i;
        ans_r = r;
        ans_p = p;
        ans_q = q;
      }
    }
    Point2 dir = Line2{lhs[ans_i], lhs[ans_i + 1]}.direction(),
           vdir = rotate90(dir);
    Polynomial2 ret{cont_t<Point2>{
      ins_LL({lhs[ans_i], lhs[ans_i] + dir}, {lhs[ans_p], lhs[ans_p] + vdir}),
      ins_LL({lhs[ans_i], lhs[ans_i] + dir}, {lhs[ans_q], lhs[ans_q] + vdir}),
      ins_LL({lhs[ans_r], lhs[ans_r] + dir}, {lhs[ans_p], lhs[ans_p] + vdir}),
      ins_LL({lhs[ans_r], lhs[ans_r] + dir}, {lhs[ans_q], lhs[ans_q] + vdir})}};
    lhs.vs.pop_back();
    return ret;
  }
  ConvexHull2 &do_minkowski_sum_nonstrict(const ConvexHull2 &rhs) {
    size_t n = vs.size(), m = rhs.vs.size();
    if (!m) return *this;
    if (!n) return *this = rhs;
    cont_t<Point2> result;
    result.reserve(n + m);
    size_t midxl = 0;
    for (size_t i = 1; i < n; ++i)
      if (vs[i] < vs[midxl]) midxl = i;
    size_t midxr = 0;
    for (size_t i = 1; i < m; ++i)
      if (rhs[i] < rhs[midxr]) midxr = i;
    bool fl = false, fr = false;
    for (size_t idxl = midxl, idxr = midxr;
         !(idxl == midxl && fl) || !(idxr == midxr && fr);) {
      Point2 diffl = vs[next(idxl)] - vs[idxl];
      Point2 diffr = rhs[rhs.next(idxr)] - rhs[idxr];
      bool f = !(idxl == midxl && fl) &&
               ((idxr == midxr && fr) || is_positive(cross_mul(diffl, diffr)));
      result.push_back(vs[idxl] + rhs[idxr] + (f ? diffl : diffr));
      (f ? idxl : idxr) = (f ? next(idxl) : rhs.next(idxr));
      (f ? fl : fr) |= !(f ? idxl : idxr);
    }
    vs = result;
    return *this;
  }
  friend ConvexHull2 minkowski_sum_nonstrict(ConvexHull2 poly,
                                             const ConvexHull2 &rhs) {
    return poly.do_minkowski_sum_nonstrict(rhs);
  }
  ConvexHull2 &do_minkowski_sum(const ConvexHull2 &rhs) {
    return do_minkowski_sum_nonstrict(rhs).init();
  }
  friend ConvexHull2 minkowski_sum(ConvexHull2 poly, const ConvexHull2 &rhs) {
    return poly.do_minkowski_sum(rhs);
  }
  ConvexHull2 &do_convex_cut(const Line2 &l) {
    size_t sz = vs.size();
    cont_t<Point2> cvc;
    for (size_t i = 0; i < sz; ++i) {
      Point2 p1 = vs[i], p2 = vs[next(i)];
      ptrdiff_t d1 = cross_sign(l.l, l.r, p1), d2 = cross_sign(l.l, l.r, p2);
      if (d1 >= 0) cvc.push_back(p1);
      if (d1 * d2 < 0) cvc.push_back(ins_LL({p1, p2}, l));
    }
    vs = cvc;
    return *this;
  }
  friend ConvexHull2 convex_cut(ConvexHull2 poly, const Line2 &l) {
    return poly.do_convex_cut(l);
  }
};
ConvexHull2 ins_hP(cont_t<Line2> vl) {
  auto check = [](const Line2 &u, const Line2 &v, const Line2 &w) -> bool {
    return w.is_include(ins_LL(u, v));
  };
  std::sort(vl.begin(), vl.end());
  std::deque<Line2> q;
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
  return ConvexHull2{ret, true};
}
}  // namespace geometry2d
using namespace geometry2d;
auto solve([[maybe_unused]] int t_) -> void {
  read_var_(int, n);
  ConvexHull2 cvh(n);
  cin >> cvh;
  cvh.init_nonstrict();
  cout << cvh.vs.size() << '\n';
  size_t now = 0;
  for_(i, 1, cvh.vs.size() - 1)
    if (is_less(cvh[i].y, cvh[now].y) ||
        (is_equal(cvh[i].y, cvh[now].y) && is_less(cvh[i].x, cvh[now].x)))
      now = i;
  for_(i, now, cvh.vs.size() - 1) cout << cvh[i] << '\n';
  if (now)
    for_(i, 0, now - 1) cout << cvh[i] << '\n';
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
