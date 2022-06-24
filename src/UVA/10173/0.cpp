#include <bits/stdc++.h>
using namespace std;
#define OPERATOR_OVERRIED_PAIR_(oper)                                                                  \
    template <typename Tp, typename Up>                                                                \
    inline std::pair<Tp, Up> &operator oper##=(std::pair<Tp, Up> &lhs, const std::pair<Tp, Up> &rhs) { \
        lhs.first oper## = rhs.first;                                                                  \
        lhs.second oper## = rhs.second;                                                                \
        return lhs;                                                                                    \
    }                                                                                                  \
    template <typename Tp, typename Up>                                                                \
    inline std::pair<Tp, Up> operator oper(std::pair<Tp, Up> lhs, const std::pair<Tp, Up> &rhs) { return lhs oper## = rhs; }
OPERATOR_OVERRIED_PAIR_(+)
OPERATOR_OVERRIED_PAIR_(-)
OPERATOR_OVERRIED_PAIR_(*)
OPERATOR_OVERRIED_PAIR_(/)
OPERATOR_OVERRIED_PAIR_(%)
#undef OPERATOR_OVERRIED_PAIR_
template <typename Tp, typename Up>
std::istream &operator>>(std::istream &is, std::pair<Tp, Up> &p) { return is >> p.first >> p.second; }
template <typename Key, typename Tp, typename Hash = std::hash<Key>>
using hmap = std::unordered_map<Key, Tp, Hash>;
template <class Tp>
auto chkmin(Tp &a, Tp b) -> bool { return b < a ? a = b, true : false; };
template <class Tp>
auto chkmax(Tp &a, Tp b) -> bool { return a < b ? a = b, true : false; };
template <typename Tp>
auto discretization(Tp &var) -> Tp {
    Tp d__(var);
    std::sort(d__.begin(), d__.end());
    d__.erase(std::unique(d__.begin(), d__.end()), d__.end());
    for (auto &i : var) i = std::distance(d__.begin(), std::lower_bound(d__.begin(), d__.end(), i));
    return d__;
};
template <typename Tp>
auto ispow2(Tp i) -> bool { return i && (i & -i) == i; }
template <class Tp, class Up>
std::ostream &operator<<(std::ostream &os, const std::pair<Tp, Up> &p) {
    if (&os == &std::cerr) return os << "(" << p.first << ", " << p.second << ")";
    return os << p.first << " " << p.second;
}
template <class Ch, class Tr, class Container>
std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os, const Container &x) {
    if (&os == &std::cerr) os << "[";
    if (&os == &std::cerr)
        for (auto it = x.begin(); it != x.end() - 1; ++it) os << *it << ", ";
    else
        for (auto it = x.begin(); it != x.end() - 1; ++it) os << *it << ' ';
    os << x.back();
    if (&os == &std::cerr) os << "]";
    return os;
}
template <typename Tp>
inline void debug(Tp x) {
}
template <typename Tp, typename... Args>
inline void debug(Tp x, Args... args) {
}
const double EPS = 1e-6;
const auto STATIC__ = []() { return 0; }();
namespace calc_geo {
using data_t = double;
template <typename Tp>
using cont_t = std::vector<Tp>;
const data_t EPS = 1e-9;
const data_t DATA_MAX = DBL_MAX;
inline ptrdiff_t sign(data_t lhs) { return lhs < -EPS ? -1 : lhs > EPS; }
inline bool is_negative(data_t x) { return sign(x) & 2; }
inline bool is_zero(data_t x) { return !sign(x); }
inline bool is_positive(data_t x) { return (sign(x) + 1) & 2; }
inline ptrdiff_t comp(data_t lhs, data_t rhs) { return sign(lhs - rhs); }
inline bool is_less(data_t lhs, data_t rhs) { return is_negative(lhs - rhs); }
inline bool is_equal(data_t lhs, data_t rhs) { return is_zero(lhs - rhs); }
inline bool is_greater(data_t lhs, data_t rhs) { return is_positive(lhs - rhs); }
inline bool is_intersect(data_t l1, data_t r1, data_t l2, data_t r2) {
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
inline bool is_in_middle(data_t l, data_t mid, data_t r) { return is_equal(l, mid) || is_equal(r, mid) || ((l < mid) ^ (r < mid)); }
struct Point2 {
    using self = Point2;
    data_t x, y;
    inline Point2(data_t x = data_t{}, data_t y = data_t{}):
        x(x), y(y) {}
    friend std::istream &operator>>(std::istream &is, self &rhs) { return is >> rhs.x >> rhs.y; }
    friend std::ostream &operator<<(std::ostream &os, const self &rhs) { return os << rhs.x << ' ' << rhs.y; }
    inline self &set_as_polar(data_t r, data_t theta) { return *this = {r * cos(theta), r * sin(theta)}; }
    friend inline self lerp(const self &lhs, const self &rhs, data_t coord) { return lhs * coord + rhs * (1 - coord); }
    friend inline self mid_point(const self &lhs, const self &rhs) { return lerp(lhs, rhs, 0.5); }
#define SCALA_OP(op)                        \
    inline self &operator op##=(data_t n) { \
        this->x op## = n;                   \
        this->y op## = n;                   \
        return *this;                       \
    }                                       \
    inline self operator op(data_t n) const { return self(*this) op## = n; }
    SCALA_OP(+)
    SCALA_OP(-)
    SCALA_OP(*)
    SCALA_OP(/)
#undef SCALA_OP
#define VEC_OP(op)                                 \
    inline self &operator op##=(const self &rhs) { \
        this->x op## = rhs.x;                      \
        this->y op## = rhs.y;                      \
        return *this;                              \
    }                                              \
    inline self operator op(const self &rhs) const { return self(*this) op## = rhs; }
    VEC_OP(+)
    VEC_OP(-)
#undef VEC_OP
    inline self operator-() const { return self{-x, -y}; }
    inline bool operator<(const self &rhs) const {
        auto c = comp(x, rhs.x);
        if (c) return c >> 1;
        return comp(y, rhs.y) >> 1;
    }
    inline bool operator==(const self &rhs) const { return is_equal(x, rhs.x) && is_equal(y, rhs.y); }
    inline bool operator!=(const self &rhs) const { return !(*this == rhs); }
    friend inline data_t dot_mul(const self &lhs, const self &rhs) { return lhs.x * rhs.x + lhs.y * rhs.y; }
    friend inline data_t cross_mul(const self &lhs, const self &rhs) { return lhs.x * rhs.y - lhs.y * rhs.x; }
#define SCALA_FUNC(name, func_body)       \
    inline data_t name() const func_body; \
    friend inline data_t name(const self &lhs) { return lhs.name(); }
    SCALA_FUNC(arg, { return atan2(y, x); })
    SCALA_FUNC(arg_2pi, { data_t tmp_= arg(); return is_negative(tmp_) ? tmp_ + 2 * acos(data_t{-1}) : tmp_; })
    SCALA_FUNC(norm, { return x * x + y * y; })
    SCALA_FUNC(abs, { return sqrt(norm()); })
    constexpr static int QUAD_STATE[3][3] = {{5, 6, 7}, {4, 0, 0}, {3, 2, 1}};
    inline int quad() const { return QUAD_STATE[sign(y) + 1][sign(x) + 1]; };
    friend inline int quad(const self &lhs) { return lhs.quad(); }
#undef SCALA_FUNC
#define SELF_FUNC(name, func_body)      \
    inline self &do_##name() func_body; \
    friend inline self name(self lhs) { return lhs.do_##name(); }
    SELF_FUNC(rotate90, { data_t tmp = x; x = -y; y = tmp; return *this; })
    SELF_FUNC(rotate180, { x = -x; y = -y; return *this; })
    SELF_FUNC(rotate270, { data_t tmp = y; y = -x; x = tmp; return *this; })
    SELF_FUNC(unit, { return *this /= abs(); })
#undef SELF_FUNC
    inline self &do_rotate(data_t theta) {
        data_t _x = x, _y = y;
        x = _x * cos(theta) - _y * sin(theta);
        y = _x * sin(theta) + _y * cos(theta);
        return *this;
    };
    friend inline self rotate(self lhs, data_t theta) { return lhs.do_rotate(theta); }
};
inline data_t dist_PP(const Point2 &lhs, const Point2 &rhs) { return hypot(lhs.x - rhs.x, lhs.y - rhs.y); }
inline data_t sqr_dist_PP(const Point2 &lhs, const Point2 &rhs) { return (lhs.x - rhs.x) * (lhs.x - rhs.x) + (lhs.y - rhs.y) * (lhs.y - rhs.y); }
inline data_t cross(const Point2 &p1, const Point2 &p2, const Point2 &p3) { return (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y); }
inline ptrdiff_t cross_sign(const Point2 &p1, const Point2 &p2, const Point2 &p3) { return sign(cross(p1, p2, p3)); }
inline data_t dot(const Point2 &p1, const Point2 &p2, const Point2 &p3) { return (p2.x - p1.x) * (p3.x - p1.x) + (p2.y - p1.y) * (p3.y - p1.y); }
inline ptrdiff_t dot_sign(const Point2 &p1, const Point2 &p2, const Point2 &p3) { return sign(dot(p1, p2, p3)); }
inline bool is_in_middle(Point2 a, Point2 m, Point2 b) { return is_in_middle(a.x, m.x, b.x) && is_in_middle(a.y, m.y, b.y); }
inline data_t ang_PP(const Point2 &p1, const Point2 &p2) { return atan2(cross_mul(p1, p2), dot_mul(p1, p2)); }
struct Line2 {
    using self = Line2;
    using point_t = Point2;
    point_t l, r;
    Line2() = default;
    inline Line2(const point_t &start_, const point_t &end_):
        l(start_), r(end_) {}
    inline Line2(const data_t &start_x, const data_t &start_y, const data_t &end_x, const data_t &end_y):
        l(start_x, start_y), r(end_x, end_y) {}
    friend std::istream &operator>>(std::istream &is, self &rhs) { return is >> rhs.l >> rhs.r; }
    friend std::ostream &operator<<(std::ostream &os, const self &rhs) { return os << rhs.l << ' ' << rhs.r; }
    inline friend bool operator<(const self &lhs, const self &rhs) {
        if (is_same_dir(lhs, rhs)) return rhs.is_include(lhs.l);
        auto vl = lhs.direction();
        auto vr = rhs.direction();
        if (vl.quad() != vr.quad()) return vl.quad() < vr.quad();
        return is_positive(cross_mul(vl, vr));
    }
    inline data_t slope() const { return (r.y - l.y) / (r.x - l.x); }
    inline data_t slope_inv() const { return (r.x - l.x) / (r.y - l.y); }
    inline data_t intercept_v() const { return r.y - r.x * slope(); }
    inline data_t intercept_h() const { return r.x - r.y * slope_inv(); }
    inline data_t lerp_y(data_t x) const { return l.y + (x - l.x) * slope(); }
    inline data_t lerp_x(data_t y) const { return l.x + (y - l.y) * slope_inv(); }
    friend inline bool is_parallel(const self &lhs, const self &rhs) { return is_zero(cross_mul(lhs.direction(), rhs.direction())); }
    friend inline bool is_same_dir(const self &lhs, const self &rhs) { return is_parallel(lhs, rhs) && is_positive(dot_mul(lhs.direction(), rhs.direction())); }
    inline point_t direction() const { return r - l; }
    inline bool is_include(const point_t &p) const { return is_positive(cross(l, r, p)); }
    inline self &do_push(data_t eps = 1e-8) {
        point_t delta = direction().do_rotate90().do_unit();
        delta *= eps;
        l += delta;
        r += delta;
        return *this;
    }
    friend inline self push(self line, data_t eps = 1e-8) { return line.do_push(eps); }
};
inline bool is_ins_LL(const Line2 &l1, const Line2 &l2) { return !is_zero(cross(l2.l, l2.r, l1.l) - cross(l2.l, l2.r, l1.r)); }
inline Point2 ins_LL(const Line2 &l1, const Line2 &l2) {
    data_t a1 = cross(l2.l, l2.r, l1.l), a2 = -cross(l2.l, l2.r, l1.r);
    return (l1.l * a2 + l1.r * a1) / (a1 + a2);
}
inline bool is_ins_SS(const Line2 &l1, const Line2 &l2) { return is_intersect(l1.l.x, l1.r.x, l2.l.x, l2.r.x) && is_intersect(l1.l.y, l1.r.y, l2.l.y, l2.r.y) && cross_sign(l1.l, l1.r, l2.l) * cross_sign(l1.l, l1.r, l2.r) <= 0 && cross_sign(l2.l, l2.r, l1.l) * cross_sign(l2.l, l2.r, l1.r) <= 0; }
inline bool is_ins_SS_strict(const Line2 &s1, const Line2 &s2) { return cross_sign(s1.l, s1.r, s2.l) * cross_sign(s1.l, s1.r, s2.r) < 0 && cross_sign(s2.l, s2.r, s1.l) * cross_sign(s2.l, s2.r, s1.r) < 0; }
inline Point2 proj(const Line2 &l1, const Point2 &p) {
    Point2 dir = l1.direction();
    return l1.l + dir * (dot_mul(dir, p - l1.l) / dir.norm());
}
inline Point2 reflect(const Line2 &l1, const Point2 &p) { return proj(l1, p) * 2 - p; }
inline bool is_on_same_L(const Point2 &p1, const Point2 &p2, const Point2 &p3) { return is_zero(cross(p1, p2, p3)); }
inline bool is_on_S(const Line2 &s1, const Point2 &p) { return is_on_same_L(s1.l, s1.r, p) && is_in_middle(s1.l, p, s1.r); }
inline bool is_on_S_strict(const Line2 &s1, const Point2 &p) { return cross_sign(s1.l, s1.r, p) == 0 && sign(dot_mul(p - s1.l, s1.l - s1.r)) * sign(dot_mul(p - s1.r, s1.l - s1.r)) < 0; }
inline data_t dist_PL(const Point2 &p, const Line2 &s1) {
    if (s1.l == s1.r) return dist_PP(s1.l, p);
    return dist_PP(p, proj(s1, p));
}
inline data_t dist_PS(const Point2 &p, const Line2 &s1) {
    if (s1.l == s1.r) return dist_PP(s1.l, p);
    Point2 h = proj(s1, p);
    if (is_in_middle(s1.l, h, s1.r)) return dist_PP(p, h);
    return std::min(dist_PP(s1.l, p), dist_PP(s1.r, p));
}
inline data_t dist_SS(const Line2 &s1, const Line2 &s2) {
    if (is_ins_SS(s1, s2)) return 0;
    return std::min({dist_PS(s1.l, s2), dist_PS(s1.r, s2), dist_PS(s2.l, s1), dist_PS(s2.r, s1)});
}
struct Polynomial2 {
    using self = Polynomial2;
    using point_t = Point2;
    cont_t<point_t> vs;
    Polynomial2() = default;
    explicit Polynomial2(size_t size_):
        vs(size_) {}
    explicit Polynomial2(const cont_t<point_t> &vs_):
        vs(vs_) {}
    friend std::istream &operator>>(std::istream &is, self &rhs) {
        for (auto &i : rhs.vs) is >> i;
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const self &rhs) {
        for (auto it = rhs.vs.begin(); it != rhs.vs.end() - 1; ++it) os << *it << ' ';
        return os << rhs.vs.back();
    }
    inline self &resort() {
        std::sort(vs.begin(), vs.end());
        return *this;
    }
    inline self &reunique() {
        resort();
        vs.erase(std::unique(vs.begin(), vs.end()), vs.end());
        return *this;
    }
    inline point_t &operator[](size_t x) { return vs[x]; }
    inline const point_t &operator[](size_t x) const { return vs[x]; }
    inline cont_t<point_t>::iterator prev(cont_t<point_t>::iterator it) {
        if (it == vs.begin()) it = vs.end();
        return --it;
    }
    inline cont_t<point_t>::const_iterator prev(cont_t<point_t>::const_iterator it) const {
        if (it == vs.begin()) it = vs.end();
        return --it;
    }
    inline cont_t<point_t>::iterator next(cont_t<point_t>::iterator it) {
        if (++it == vs.end()) it = vs.begin();
        return it;
    }
    inline cont_t<point_t>::const_iterator next(cont_t<point_t>::const_iterator it) const {
        if (++it == vs.end()) it = vs.begin();
        return it;
    }
    inline size_t prev(size_t idx) const { return (idx + vs.size() - 1) % vs.size(); }
    inline size_t next(size_t idx) const { return (idx + 1) % vs.size(); }
#define SCALA_FUNC(name, func_body)       \
    inline data_t name() const func_body; \
    friend inline data_t name(const self &lhs) { return lhs.name(); }
    SCALA_FUNC(circum, {
        data_t result{};
        for (size_t i = 0; i < vs.size(); ++i) result += dist_PP(vs[i], vs[next(i)]);
        return result;
    })
    SCALA_FUNC(area, {
        data_t result{};
        for (size_t i = 0; i < vs.size(); ++i) result += cross_mul(vs[i], vs[next(i)]);
        return result / 2;
    })
#undef SCALA_FUNC
    static const size_t inside_or_onborder = 3;
    static const size_t inside = 2;
    static const size_t onborder = 1;
    static const size_t outside = 0;
    virtual inline size_t relation_P(const point_t &p) const {
        bool result = false;
        for (size_t i = 0; i < vs.size(); ++i) {
            point_t now_p = vs[i], next_p = vs[next(i)];
            if (is_on_S({now_p, next_p}, p)) return self::onborder;
            if (!is_greater(now_p.y, next_p.y)) std::swap(now_p, next_p);
            if (is_greater(p.y, now_p.y) || !is_greater(p.y, next_p.y)) continue;
            result ^= cross_sign(p, now_p, next_p) > 0;
        }
        return result ? self::inside : self::outside;
    }
};
struct ConvexHull2: public Polynomial2 {
    using self = ConvexHull2;
    using base = Polynomial2;
    using point_t = Point2;
    ConvexHull2() = default;
    explicit ConvexHull2(size_t size_):
        Polynomial2(size_) {}
    explicit ConvexHull2(const cont_t<point_t> &vs_, bool inited = false, bool strict = true):
        Polynomial2(vs_) {
        if (!inited) strict ? init() : init_nonstrict();
    }
    friend std::istream &operator>>(std::istream &is, self &rhs) {
        for (auto &i : rhs.vs) is >> i;
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const self &rhs) {
        for (auto it = rhs.vs.begin(); it != rhs.vs.end() - 1; ++it) os << *it << ' ';
        return os << rhs.vs.back();
    }
    inline self &init() {
        ptrdiff_t sz = vs.size();
        if (sz <= 1) return *this;
        resort();
        cont_t<point_t> cvh(sz * 2);
        ptrdiff_t sz_cvh = 0;
        for (ptrdiff_t i = 0; i < sz; cvh[sz_cvh++] = vs[i++])
            while (sz_cvh > 1 && cross_sign(cvh[sz_cvh - 2], cvh[sz_cvh - 1], vs[i]) <= 0) --sz_cvh;
        for (ptrdiff_t i = sz - 2, t = sz_cvh; ~i; cvh[sz_cvh++] = vs[i--])
            while (sz_cvh > t && cross_sign(cvh[sz_cvh - 2], cvh[sz_cvh - 1], vs[i]) <= 0) --sz_cvh;
        cvh.resize(sz_cvh - 1);
        vs = cvh;
        return *this;
    };
    inline self &init_nonstrict() {
        reunique();
        ptrdiff_t sz = vs.size();
        if (sz <= 1) return *this;
        cont_t<point_t> cvh(sz * 2);
        ptrdiff_t sz_cvh = 0;
        for (ptrdiff_t i = 0; i < sz; cvh[sz_cvh++] = vs[i++])
            while (sz_cvh > 1 && cross_sign(cvh[sz_cvh - 2], cvh[sz_cvh - 1], vs[i]) < 0) --sz_cvh;
        for (ptrdiff_t i = sz - 2, t = sz_cvh; ~i; cvh[sz_cvh++] = vs[i--])
            while (sz_cvh > t && cross_sign(cvh[sz_cvh - 2], cvh[sz_cvh - 1], vs[i]) < 0) --sz_cvh;
        cvh.resize(sz_cvh - 1);
        vs = cvh;
        return *this;
    };
    inline size_t relation_P(const point_t &p) const override {
        if (vs.size() == 1) return vs.front() == p ? base::inside_or_onborder : base::outside;
        if (vs.size() == 2) return is_on_S({vs.front(), vs.back()}, p) ? base::inside_or_onborder : base::outside;
        if (is_positive(cross(vs.front(), p, vs[1])) || is_positive(cross(vs.front(), vs.back(), p))) return base::outside;
        auto it = std::lower_bound(vs.begin() + 1, vs.end(), p, [&](const point_t &lhs, const point_t &rhs) { return is_positive(cross(vs.front(), lhs, rhs)); }) - 1;
        auto next_it = next(it);
        auto res = cross_sign(p, *it, *next_it);
        if (res) return ~res ? base::inside_or_onborder : base::outside;
        return !res && !is_positive(dot(p, *it, *next_it)) ? base::inside_or_onborder : base::outside;
    }
    friend inline base coverage_rect_with_min_area(self &lhs) {
        size_t sz = lhs.vs.size();
        if (sz == 0) return lhs;
        if (sz == 1) return base{cont_t<point_t>{lhs[0], lhs[0], lhs[0], lhs[0]}};
        if (sz == 2) return base{cont_t<point_t>{lhs[0], lhs[0], lhs[1], lhs[1]}};
        lhs.vs.push_back(lhs.vs[0]);
        data_t ans = DATA_MAX;
        size_t r = 1, p = 1, q;
        size_t ans_i, ans_r, ans_p, ans_q;
        for (size_t i = 0; i < sz; ++i) {
            while (!is_negative(cross(lhs.vs[i], lhs.vs[i + 1], lhs.vs[r + 1]) - cross(lhs.vs[i], lhs.vs[i + 1], lhs.vs[r]))) r = (r + 1) % sz;
            while (!is_negative(dot(lhs.vs[i], lhs.vs[i + 1], lhs.vs[p + 1]) - dot(lhs.vs[i], lhs.vs[i + 1], lhs.vs[p]))) p = (p + 1) % sz;
            if (i == 0) q = p;
            while (!is_positive(dot(lhs.vs[i], lhs.vs[i + 1], lhs.vs[q + 1]) - dot(lhs.vs[i], lhs.vs[i + 1], lhs.vs[q]))) q = (q + 1) % sz;
            data_t tmp = cross(lhs.vs[i], lhs.vs[i + 1], lhs.vs[r]) * (dot(lhs.vs[i], lhs.vs[i + 1], lhs.vs[p]) - dot(lhs.vs[i], lhs.vs[i + 1], lhs.vs[q])) / (lhs.vs[i] - lhs.vs[i + 1]).norm();
            if (ans > tmp) {
                ans = tmp;
                ans_i = i;
                ans_r = r;
                ans_p = p;
                ans_q = q;
            }
        }
        Point2 dir = Line2{lhs[ans_i], lhs[ans_i + 1]}.direction(), vdir = rotate90(dir);
        Line2 li{lhs[ans_i], lhs[ans_i] + dir}, lp{lhs[ans_p], lhs[ans_p] + vdir}, lr{lhs[ans_r], lhs[ans_r] + dir}, lq{lhs[ans_q], lhs[ans_q] + vdir};
        Polynomial2 ret{cont_t<point_t>{ins_LL(li, lp), ins_LL(lp, lr), ins_LL(lr, lq), ins_LL(lq, li)}};
        lhs.vs.pop_back();
        return ret;
    }
};
}  // namespace calc_geo
using namespace calc_geo;
inline auto solve([[maybe_unused]] int t_) -> void {
    int n;
    while ((cin >> n), n) {
        ConvexHull2 cvh(n);
        cin >> cvh;
        cout << coverage_rect_with_min_area(cvh.init()).area() << '\n';
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int i_ = STATIC__;
    cout << fixed << setprecision(4);
    debug("Case", i_), solve(i_);
    return 0;
}
