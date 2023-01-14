#include <bits/stdc++.h>
using namespace std;
template <typename Tp>
using vc = std::vector<Tp>;
#define for_(i, l, r, vars...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vars; i <= i##end; ++i)
#define foreach_ref_(i, container) for (auto &i : (container))
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
const double EPS = 1e-6;
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
  friend std::istream &operator>>(std::istream &is, self &rhs) {
    return is >> rhs.x >> rhs.y;
  }
  friend std::ostream &operator<<(std::ostream &os, const self &rhs) {
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
  bool operator!=(const self &rhs) const { return !(*this == rhs); }
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
  int quad() const {
    return std::array<std::array<int, 3>, 3>{
      std::array<int, 3>{5, 6, 7},
      std::array<int, 3>{4, 0, 0},
      std::array<int, 3>{3, 2, 1}}[sign(y) + 1][sign(x) + 1];
  };
  friend int quad(const self &lhs) { return lhs.quad(); }
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
struct Line2 {
  using self = Line2;
  using point_t = Point2;
  point_t l, r;
  Line2() = default;
  Line2(const point_t &start_, const point_t &end_): l(start_), r(end_) {}
  Line2(const data_t &start_x,
        const data_t &start_y,
        const data_t &end_x,
        const data_t &end_y)
    : l(start_x, start_y), r(end_x, end_y) {}
  friend std::istream &operator>>(std::istream &is, self &rhs) {
    return is >> rhs.l >> rhs.r;
  }
  friend std::ostream &operator<<(std::ostream &os, const self &rhs) {
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
bool is_on_same_L(const Point2 &p1, const Point2 &p2, const Point2 &p3) {
  return is_zero(cross(p1, p2, p3));
}
bool is_on_S(const Line2 &s1, const Point2 &p) {
  return is_on_same_L(s1.l, s1.r, p) && is_in_middle(s1.l, p, s1.r);
}
bool is_on_S_strict(const Line2 &s1, const Point2 &p) {
  return cross_sign(s1.l, s1.r, p) == 0 &&
         sign(dot_mul(p - s1.l, s1.l - s1.r)) *
             sign(dot_mul(p - s1.r, s1.l - s1.r)) <
           0;
}
struct Polynomial2 {
  using self = Polynomial2;
  using point_t = Point2;
  cont_t<point_t> vs;
  Polynomial2() = default;
  explicit Polynomial2(size_t size_): vs(size_) {}
  explicit Polynomial2(const cont_t<point_t> &vs_): vs(vs_) {}
  self &resort() {
    std::sort(vs.begin(), vs.end());
    return *this;
  }
  self &reunique() {
    resort();
    vs.erase(std::unique(vs.begin(), vs.end()), vs.end());
    return *this;
  }
  point_t &operator[](size_t x) { return vs[x]; }
  const point_t &operator[](size_t x) const { return vs[x]; }
  size_t prev(size_t idx) const { return (idx + vs.size() - 1) % vs.size(); }
  size_t next(size_t idx) const { return (idx + 1) % vs.size(); }
};
struct ConvexHull2: public Polynomial2 {
  using self = ConvexHull2;
  using base = Polynomial2;
  using point_t = Point2;
  ConvexHull2() = default;
  explicit ConvexHull2(size_t size_): Polynomial2(size_) {}
  explicit ConvexHull2(const cont_t<point_t> &vs_,
                       bool inited = false,
                       bool strict = true)
    : Polynomial2(vs_) {
    if (!inited) strict ? init() : init_nonstrict();
  }
  self &init() {
    ptrdiff_t sz = vs.size();
    if (sz <= 1) return *this;
    resort();
    cont_t<point_t> cvh(sz * 2);
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
  };
  self &init_nonstrict() {
    reunique();
    ptrdiff_t sz = vs.size();
    if (sz <= 1) return *this;
    cont_t<point_t> cvh(sz * 2);
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
  };
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
  };
  friend base coverage_rect_with_min_area(self &lhs) {
    size_t sz = lhs.vs.size();
    if (sz == 0) return lhs;
    if (sz == 1) return base{cont_t<point_t>{lhs[0], lhs[0], lhs[0], lhs[0]}};
    if (sz == 2) return base{cont_t<point_t>{lhs[0], lhs[0], lhs[1], lhs[1]}};
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
    point_t dir = Line2{lhs[ans_i], lhs[ans_i + 1]}.direction(),
            vdir = rotate90(dir);
    base ret{cont_t<point_t>{
      ins_LL({lhs[ans_i], lhs[ans_i] + dir}, {lhs[ans_p], lhs[ans_p] + vdir}),
      ins_LL({lhs[ans_i], lhs[ans_i] + dir}, {lhs[ans_q], lhs[ans_q] + vdir}),
      ins_LL({lhs[ans_r], lhs[ans_r] + dir}, {lhs[ans_p], lhs[ans_p] + vdir}),
      ins_LL({lhs[ans_r], lhs[ans_r] + dir}, {lhs[ans_q], lhs[ans_q] + vdir})}};
    lhs.vs.pop_back();
    return ret;
  }
  friend base coverage_rect_with_min_circum(self &lhs) {
    size_t sz = lhs.vs.size();
    if (sz == 0) return lhs;
    if (sz == 1) return base{cont_t<point_t>{lhs[0], lhs[0], lhs[0], lhs[0]}};
    if (sz == 2) return base{cont_t<point_t>{lhs[0], lhs[0], lhs[1], lhs[1]}};
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
    point_t dir = Line2{lhs[ans_i], lhs[ans_i + 1]}.direction(),
            vdir = rotate90(dir);
    base ret{cont_t<point_t>{
      ins_LL({lhs[ans_i], lhs[ans_i] + dir}, {lhs[ans_p], lhs[ans_p] + vdir}),
      ins_LL({lhs[ans_i], lhs[ans_i] + dir}, {lhs[ans_q], lhs[ans_q] + vdir}),
      ins_LL({lhs[ans_r], lhs[ans_r] + dir}, {lhs[ans_p], lhs[ans_p] + vdir}),
      ins_LL({lhs[ans_r], lhs[ans_r] + dir}, {lhs[ans_q], lhs[ans_q] + vdir})}};
    lhs.vs.pop_back();
    return ret;
  }
  self &do_minkowski_sum_nonstrict(const self &rhs) {
    size_t n = vs.size(), m = rhs.vs.size();
    if (!m) return *this;
    if (!n) return *this = rhs;
    cont_t<point_t> result;
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
      point_t diffl = vs[next(idxl)] - vs[idxl];
      point_t diffr = rhs[rhs.next(idxr)] - rhs[idxr];
      bool f = !(idxl == midxl && fl) &&
               ((idxr == midxr && fr) || is_positive(cross_mul(diffl, diffr)));
      result.push_back(vs[idxl] + rhs[idxr] + (f ? diffl : diffr));
      (f ? idxl : idxr) = (f ? next(idxl) : rhs.next(idxr));
      (f ? fl : fr) |= !(f ? idxl : idxr);
    }
    vs = result;
    return *this;
  }
  friend self minkowski_sum_nonstrict(self poly, const self &rhs) {
    return poly.do_minkowski_sum_nonstrict(rhs);
  }
  self &do_minkowski_sum(const self &rhs) {
    return do_minkowski_sum_nonstrict(rhs).init();
  }
  friend self minkowski_sum(self poly, const self &rhs) {
    return poly.do_minkowski_sum(rhs);
  }
  self &do_convex_cut(const Line2 &l) {
    size_t sz = vs.size();
    cont_t<point_t> cvc;
    for (size_t i = 0; i < sz; ++i) {
      point_t p1 = vs[i], p2 = vs[next(i)];
      ptrdiff_t d1 = cross_sign(l.l, l.r, p1), d2 = cross_sign(l.l, l.r, p2);
      if (d1 >= 0) cvc.push_back(p1);
      if (d1 * d2 < 0) cvc.push_back(ins_LL({p1, p2}, l));
    }
    vs = cvc;
    return *this;
  }
  friend self convex_cut(self poly, const Line2 &l) {
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
}  // namespace calc_geo
using namespace calc_geo;
auto solve([[maybe_unused]] int t_) -> void {
  int n;
  while ((cin >> n), n) {
    read_container_(vc<Point2>, vp, n);
    vc<Line2> vl;
    vl.emplace_back(vp.back(), vp.front());
    for_(i, 0, n - 2) vl.emplace_back(vp[i], vp[i + 1]);
    ConvexHull2 cvh = ins_hP(vl);
    cout << (cvh.reunique().vs.size() > 1) << '\n';
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int i_ = 0;
  cout << fixed << setprecision(6);
  solve(i_);
  return 0;
}
