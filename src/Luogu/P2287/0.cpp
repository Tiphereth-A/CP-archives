#include <bits/stdc++.h>
#define CEXP constexpr
#define TPN typename
#define CR const &
#define fle_(T, i, l, r, ...) \
  for (T i = (l), i##e = (r)__VA_OPT__(, ) __VA_ARGS__; i <= i##e; ++i)
#define flt_(T, i, l, r, ...) \
  for (T i = (l), i##e = (r)__VA_OPT__(, ) __VA_ARGS__; i < i##e; ++i)
#undef assert
#define assert(x) 42
using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using i128 = __int128_t;
using isz = ptrdiff_t;
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;
using usz = size_t;
using f64 = double;
template <class T>
using ptt = std::pair<T, T>;
template <class T>
using pt3 = std::tuple<T, T, T>;
template <class T>
using pt4 = std::tuple<T, T, T, T>;
template <class E>
using itl = std::initializer_list<E>;
template <class T>
using vec = std::vector<T>;
template <class T>
using vvec = vec<vec<T>>;
template <class T>
using v3ec = vec<vvec<T>>;
template <class T>
using vecpt = vec<ptt<T>>;
template <class T>
using vvecpt = vvec<ptt<T>>;
template <class T>
using ptvec = ptt<vec<T>>;
template <class T>
using ptvvec = ptt<vvec<T>>;
template <class T, usz ext = std::dynamic_extent>
using spn = std::span<T const, ext>;
#define mk_(V, A, T) using V##A = V<T>;
#define mk(A, T)                                                              \
  mk_(ptt, A, T) mk_(pt3, A, T) mk_(pt4, A, T) mk_(vec, A, T) mk_(vvec, A, T) \
    mk_(v3ec, A, T) mk_(vecpt, A, T) mk_(vvecpt, A, T) mk_(ptvec, A, T)       \
      mk_(ptvvec, A, T) mk_(spn, A, T) mk_(itl, A, T)
mk(b, bool) mk(i, i32) mk(u, u32) mk(ii, i64) mk(uu, u64);
#undef mk
#undef mk_
using namespace std::literals;
CEXP i8 operator""_i8(unsigned long long x) { return (i8)x; }
CEXP i16 operator""_i16(unsigned long long x) { return (i16)x; }
CEXP i32 operator""_i32(unsigned long long x) { return (i32)x; }
CEXP i64 operator""_i64(unsigned long long x) { return (i64)x; }
CEXP isz operator""_iz(unsigned long long x) { return (isz)x; }
CEXP u8 operator""_u8(unsigned long long x) { return (u8)x; }
CEXP u16 operator""_u16(unsigned long long x) { return (u16)x; }
CEXP u32 operator""_u32(unsigned long long x) { return (u32)x; }
CEXP u64 operator""_u64(unsigned long long x) { return (u64)x; }
CEXP usz operator""_uz(unsigned long long x) { return (usz)x; }
template <std::floating_point FP>
inline FP eps_v = std::sqrt(std::numeric_limits<FP>::epsilon());
template <std::floating_point FP>
CEXP void set_eps(FP v) {
  eps_v<FP> = v;
}
using std::numbers::pi_v;
namespace tifa_libs {
using std::min, std::max, std::swap;
template <class T>
constexpr T abs(T x) {
  return x < 0 ? -x : x;
}
}  // namespace tifa_libs
namespace tifa_libs {
template <class T>
concept iterable_c = requires(T v) {
  { v.begin() } -> std::same_as<TPN T::iterator>;
  { v.end() } -> std::same_as<TPN T::iterator>;
};
template <class T>
concept container_c =
  iterable_c<T> &&
  !std::derived_from<T, std::basic_string<TPN T::value_type>> &&
  !std::derived_from<T, std::basic_string_view<TPN T::value_type>>;
template <class T>
CEXP bool is_char_v =
  std::is_same_v<T, char> || std::is_same_v<T, signed char> ||
  std::is_same_v<T, unsigned char>;
template <class T>
concept char_c = is_char_v<T>;
template <class T>
CEXP bool is_s128_v =
  std::is_same_v<T, __int128_t> || std::is_same_v<T, __int128>;
template <class T>
concept s128_c = is_s128_v<T>;
template <class T>
CEXP bool is_u128_v =
  std::is_same_v<T, __uint128_t> || std::is_same_v<T, unsigned __int128>;
template <class T>
concept u128_c = is_u128_v<T>;
template <class T>
CEXP bool is_i128_v = is_s128_v<T> || is_u128_v<T>;
template <class T>
concept i128_c = is_u128_v<T>;
template <class T>
CEXP bool is_int_v = std::is_integral_v<T> || is_i128_v<T>;
template <class T>
concept int_c = is_int_v<T>;
template <class T>
CEXP bool is_sint_v = is_s128_v<T> || (is_int_v<T> && std::is_signed_v<T>);
template <class T>
concept sint_c = is_sint_v<T>;
template <class T>
CEXP bool is_uint_v = is_u128_v<T> || (is_int_v<T> && std::is_unsigned_v<T>);
template <class T>
concept uint_c = is_uint_v<T>;
template <class T>
concept mint_c = requires(T x) {
  { x.mod() } -> uint_c;
  { x.val() } -> uint_c;
};
template <class T>
concept dft_c = requires(T x, vec<TPN T::data_t> v, u32 n) {
  { x.size() } -> std::same_as<u32>;
  x.bzr(n);
  x.dif(v, n);
  x.dit(v, n);
};
template <class T>
concept ntt_c = dft_c<T> && requires(T x) {
  T::max_size;
  T::G;
};
template <class T>
CEXP bool is_arithm_v = std::is_arithmetic_v<T> || is_int_v<T>;
template <class T>
concept arithm_c = is_arithm_v<T>;
template <class T>
struct to_sint: std::make_signed<T> {};
template <>
struct to_sint<u128> {
  using type = u128;
};
template <>
struct to_sint<i128> {
  using type = u128;
};
template <class T>
struct to_uint: std::make_unsigned<T> {};
template <>
struct to_uint<u128> {
  using type = u128;
};
template <>
struct to_uint<i128> {
  using type = u128;
};
}  // namespace tifa_libs
namespace tifa_libs {
template <sint_c T>
CEXP int sgn(T x) {
  return (!!x) | (x >> (sizeof(T) * 8 - 1));
}
template <uint_c T>
CEXP int sgn(T x) {
  return !!x;
}
template <std::floating_point FP>
CEXP int sgn(FP x) {
  return (x > eps_v<FP>)-(x < -eps_v<FP>);
}
template <class FP>
CEXP bool is_neg(FP x) {
  return sgn(x) < 0;
}
template <class FP>
CEXP bool is_zero(FP x) {
  return !sgn(x);
}
template <class FP>
CEXP bool is_pos(FP x) {
  return sgn(x) > 0;
}
template <int_c T>
CEXP int comp(T l, T r) {
  return sgn(l - r);
}
template <std::floating_point FP>
CEXP int comp(FP l, FP r) {
  return sgn((l - r) / max({abs(l), abs(r), FP(1)}));
}
template <class FP>
CEXP bool is_lt(FP l, FP r) {
  return comp(l, r) < 0;
}
template <class FP>
CEXP bool is_eq(FP l, FP r) {
  return !comp(l, r);
}
template <class FP>
CEXP bool is_gt(FP l, FP r) {
  return comp(l, r) > 0;
}
}  // namespace tifa_libs
namespace tifa_libs::geo {
template <class P>
CEXP auto cross(P CR o, P CR a, P CR b) {
  return (a - o) ^ (b - o);
}
template <class P>
requires std::floating_point<typename P::FP_t>
CEXP auto cross_unit(P CR o, P CR a, P CR b) {
  return (a - o).do_unit() ^ (b - o).do_unit();
}
template <class P>
requires std::floating_point<typename P::FP_t>
CEXP int sgn_cross(P CR o, P CR a, P CR b) {
  return sgn(cross_unit(o, a, b));
}
template <class P>
CEXP int sgn_cross(P CR o, P CR a, P CR b) {
  return sgn(cross(o, a, b));
}
}  // namespace tifa_libs::geo
namespace tifa_libs::geo {
template <class FP>
struct point3d {
  using FP_t = FP;
  FP x, y, z;
  explicit CEXP point3d(FP x = FP{}, FP y = FP{}, FP z = FP{})
    : x(x), y(y), z(z) {}
  friend std::istream &operator>>(std::istream &is, point3d &p) {
    return is >> p.x >> p.y >> p.z;
  }
  friend std::ostream &operator<<(std::ostream &os, point3d CR p) {
    return os << p.x << ' ' << p.y << ' ' << p.z;
  }
  friend CEXP point3d lerp(point3d CR s, point3d CR t, FP r) {
    static_assert(std::floating_point<FP>);
    return s * r + t * (1 - r);
  }
  friend CEXP point3d mid_point(point3d CR s, point3d CR t) {
    return lerp(s, t, .5);
  }
  CEXP point3d &operator+=(FP n) {
    return this->x += n, this->y += n, this->z += n, *this;
  }
  CEXP point3d operator+(FP n) const { return point3d(*this) += n; }
  CEXP point3d &operator-=(FP n) {
    return this->x -= n, this->y -= n, this->z -= n, *this;
  }
  CEXP point3d operator-(FP n) const { return point3d(*this) -= n; }
  CEXP point3d &operator*=(FP n) {
    return this->x *= n, this->y *= n, this->z *= n, *this;
  }
  CEXP point3d operator*(FP n) const { return point3d(*this) *= n; }
  CEXP point3d &operator/=(FP n) {
    return this->x /= n, this->y /= n, this->z /= n, *this;
  }
  CEXP point3d operator/(FP n) const { return point3d(*this) /= n; }
  CEXP point3d &operator+=(point3d CR p) {
    return this->x += p.x, this->y += p.y, this->z += p.z, *this;
  }
  CEXP point3d operator+(point3d CR p) const { return point3d(*this) += p; }
  CEXP point3d &operator-=(point3d CR p) {
    return this->x -= p.x, this->y -= p.y, this->z -= p.z, *this;
  }
  CEXP point3d operator-(point3d CR p) const { return point3d(*this) -= p; }
  CEXP point3d operator-() const { return point3d{-x, -y, -z}; }
  CEXP auto operator<=>(point3d CR p) const {
    if (auto c = comp(x, p.x); c) return c;
    if (auto c = comp(y, p.y); c) return c;
    return comp(z, p.z);
  }
  CEXP bool operator==(point3d CR p) const {
    return is_eq(x, p.x) && is_eq(y, p.y) && is_eq(z, p.z);
  }
  CEXP FP operator*(point3d CR p) const { return x * p.x + y * p.y + z * p.z; }
  CEXP point3d operator^(point3d CR p) const {
    return point3d{y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x};
  }
  CEXP auto norm2() const { return x * x + y * y + z * z; }
  CEXP auto norm() const {
    static_assert(std::floating_point<FP>);
    return std::hypot(x, y, z);
  }
  CEXP point3d &do_unit() { return *this /= norm(); }
  CEXP point3d &do_rotx(FP theta) {
    const FP y0 = y, z0 = z, ct = std::cos(theta), st = std::sin(theta);
    return y = y0 * ct - z0 * st, z = y0 * st + z0 * ct, *this;
  }
  CEXP point3d &do_roty(FP theta) {
    const FP x0 = x, z0 = z, ct = std::cos(theta), st = std::sin(theta);
    return z = z0 * ct - x0 * st, x = z0 * st + x0 * ct, *this;
  }
  CEXP point3d &do_rotz(FP theta) {
    const FP x0 = x, y0 = y, ct = std::cos(theta), st = std::sin(theta);
    return x = x0 * ct - y0 * st, y = x0 * st + y0 * ct, *this;
  }
  CEXP point3d &do_rot(point3d e, FP theta) {
    e.do_unit();
    const FP a = e.x, b = e.y, c = e.z, x0 = x, y0 = y, z0 = z,
             ct = std::cos(theta), st = std::sin(theta);
    x = x0 * (ct + a * a * (1 - ct)) + y0 * (a * b * (1 - ct) - c * st) +
        z0 * (a * c * (1 - ct) + b * st);
    y = x0 * (a * b * (1 - ct) + c * st) + y0 * (ct + b * b * (1 - ct)) +
        z0 * (b * c * (1 - ct) - a * st);
    z = x0 * (a * c * (1 - ct) - b * st) + y0 * (b * c * (1 - ct) + a * st) +
        z0 * (ct + c * c * (1 - ct));
    return *this;
  }
};
}  // namespace tifa_libs::geo
namespace tifa_libs::geo {
template <class FP>
struct line3d {
  point3d<FP> l, r;
  CEXP line3d(point3d<FP> CR s, point3d<FP> CR t): l(s), r(t) {}
  friend std::istream &operator>>(std::istream &is, line3d &l) {
    return is >> l.l >> l.r;
  }
  friend std::ostream &operator<<(std::ostream &os, line3d CR l) {
    return os << l.l << ' ' << l.r;
  }
};
}  // namespace tifa_libs::geo
namespace tifa_libs::geo {
template <class FP>
CEXP FP dist3_PL(point3d<FP> CR p, line3d<FP> CR l) {
  return cross(l.l, l.r, p).norm() / (l.r - l.l).norm();
}
}  // namespace tifa_libs::geo
namespace tifa_libs::geo {
template <class FP>
CEXP FP dist3_PP(point3d<FP> CR a, point3d<FP> CR b) {
  return (a - b).norm();
}
}  // namespace tifa_libs::geo
namespace tifa_libs::geo {
template <class FP>
struct planev {
  point3d<FP> const *u, *v, *w;
  CEXP planev(point3d<FP> CR a, point3d<FP> CR b, point3d<FP> CR c)
    : u(&a), v(&b), w(&c) {}
  friend std::ostream &operator<<(std::ostream &os, planev CR pl) {
    return os << *pl.u << ' ' << *pl.v << ' ' << *pl.w;
  }
  CEXP point3d<FP> normal() const { return cross(*u, *v, *w); }
  CEXP FP area2() const { return normal().norm(); }
  CEXP FP area() const { return area2() * (FP).5; }
  CEXP point3d<FP> CR get(u32 i) const {
    assert(i < 3);
    return **(&(this->u) + i);
  }
};
}  // namespace tifa_libs::geo
namespace tifa_libs::geo {
enum RELPLP { above_plp, in_plp, below_plp };
template <class FP>
CEXP RELPLP relation_PlP(planev<FP> CR pl, point3d<FP> CR p) {
  const FP d = (p - *pl.u) * pl.normal();
  if (is_pos(d)) return above_plp;
  if (is_neg(d)) return below_plp;
  return in_plp;
}
}  // namespace tifa_libs::geo
namespace tifa_libs::geo {
template <class FP>
CEXP FP sdist3_PlP(planev<FP> pl, point3d<FP> CR p) {
  return (p - *pl.u) * pl.normal() / pl.normal().norm();
}
}  // namespace tifa_libs::geo
namespace tifa_libs::geo {
template <class FP>
class cvh3d {
  struct facet {
    u32 n[3], id, vistime = 0;
    bool isdel = 0;
    planev<FP> p;
    u32 pid[3];
    CEXP facet() {}
    CEXP facet(u32 id, vec<point3d<FP>> CR vp, u32 id0, u32 id1, u32 id2)
      : id(id), p(vp[id0], vp[id1], vp[id2]), pid{id0, id1, id2} {}
    CEXP facet(vec<point3d<FP>> CR vp, u32 id0, u32 id1, u32 id2)
      : facet(0, vp, id0, id1, id2) {}
    CEXP void in(u32 n1, u32 n2, u32 n3) { n[0] = n1, n[1] = n2, n[2] = n3; }
  };
  u32 tm = 0, idx = 0;
  FP suf_area = 0;

public:
  vec<facet> faces;
  explicit cvh3d(vec<point3d<FP>> CR vp) {
    faces.emplace_back(vp, 0, 0, 0);
    vvecu ptsid(5);
    {
#define v(n, i) vp[n##id[i]]
      u32 pid[6]{1, 1, 1, 1, 1, 1};
      flt_(u32, i, 2, (u32)vp.size()) {
        if (is_gt(vp[i].x, v(p, 0).x)) pid[0] = i;
        if (is_gt(v(p, 1).x, vp[i].x)) pid[1] = i;
        if (is_gt(vp[i].y, v(p, 2).y)) pid[2] = i;
        if (is_gt(v(p, 3).y, vp[i].y)) pid[3] = i;
        if (is_gt(vp[i].z, v(p, 4).z)) pid[4] = i;
        if (is_gt(v(p, 5).z, vp[i].z)) pid[5] = i;
      }
      u32 sid[4]{pid[0], pid[0], pid[0], pid[0]};
      flt_(u32, i, 0, 6)
        flt_(u32, j, i + 1, 6) if (is_gt(dist3_PP(v(p, i), v(p, j)),
                                         dist3_PP(v(s, 0), v(s, 1))))
          sid[0] = pid[i],
          sid[1] = pid[j];
      flt_(u32, i, 0, 6) if (is_gt(dist3_PL(v(p, i), {v(s, 0), v(s, 1)}),
                                   dist3_PL(v(s, 2), {v(s, 0), v(s, 1)})))
        sid[2] = pid[i];
      flt_(u32,
           i,
           1,
           (u32)vp.size()) if (is_gt(abs(sdist3_PlP(planev<FP>{v(s, 0),
                                                               v(s, 1),
                                                               v(s, 2)},
                                                    vp[i])),
                                     abs(sdist3_PlP(
                                       planev<FP>{v(s, 0), v(s, 1), v(s, 2)},
                                       v(s, 3))))) sid[3] = i;
      if (is_neg(sdist3_PlP(planev<FP>{v(s, 0), v(s, 1), v(s, 2)}, v(s, 3))))
        swap(sid[1], sid[2]);
      faces.emplace_back(1, vp, sid[0], sid[2], sid[1]),
        faces.emplace_back(2, vp, sid[0], sid[1], sid[3]);
      faces.emplace_back(3, vp, sid[1], sid[2], sid[3]),
        faces.emplace_back(4, vp, sid[2], sid[0], sid[3]);
      faces[1].in(4, 3, 2), faces[2].in(1, 3, 4), faces[3].in(1, 4, 2),
        faces[4].in(1, 2, 3);
      flt_(u32, i, 1, (u32)vp.size()) {
        if (vp[i] == v(s, 0) || vp[i] == v(s, 1) || vp[i] == v(s, 2) ||
            vp[i] == v(s, 3))
          continue;
        fle_(u32, j, 1, 4) if (relation_PlP(faces[j].p, vp[i]) == above_plp) {
          ptsid[j].push_back(i);
          break;
        }
      }
      idx = 1;
#undef v
    }
    struct edge {
      u32 netid, facetid;
    };
    vec<edge> e1(vp.size()), e2(vp.size());
    vecu vistime(vp.size()), resfdel(vp.size()), resfnew(vp.size()),
      resptid(vp.size());
    auto horizon = [&](auto &&f, u32 id, point3d<FP> CR p) -> u32 {
      if (relation_PlP(faces[id].p, p) != above_plp) return 0;
      if (faces[id].vistime == tm) return -1_u32;
      faces[id].vistime = tm, faces[id].isdel = 1,
      resfdel.push_back(faces[id].id);
      u32 ret = -2_u32;
      flt_(u32, i, 0, 3) if (u32 res = f(f, faces[id].n[i], p); !res) {
        u32 pt[2]{faces[id].pid[i], faces[id].pid[(i + 1) % 3]};
        flt_(u32, j, 0, 2) if (vistime[pt[j]] != tm)
          vistime[pt[j]] = tm,
          e1[pt[j]].netid = pt[j ^ 1], e1[pt[j]].facetid = faces[id].n[i];
        else e2[pt[j]].netid = pt[j ^ 1], e2[pt[j]].facetid = faces[id].n[i];
        ret = pt[0];
      }
      else if ((int)res > 0) ret = res; return ret;
    };
    std::queue<u32> que({idx});
    for (auto i : faces[idx].n) que.push(i);
    u32 snew = 0;
    while (!que.empty()) {
      u32 nf = que.front();
      que.pop();
      if (faces[nf].isdel) continue;
      if (ptsid[nf].empty()) {
        snew = nf;
        continue;
      }
      u32 pid = ptsid[nf][0];
      point3d<FP> p = vp[pid];
      flt_(u32, i, 1, (u32)ptsid[nf].size()) if (is_gt(
                                                   sdist3_PlP(faces[nf].p,
                                                              vp[ptsid[nf][i]]),
                                                   sdist3_PlP(faces[nf].p, p)))
        p = vp[pid = ptsid[nf][i]];
      ++tm, resfdel.clear();
      u32 s = horizon(horizon, nf, p);
      ++tm, resfnew.clear();
      u32 from = 0, lastf = 0, fstf = 0;
      while (vistime[s] != tm) {
        vistime[s] = tm;
        u32 net, f, fnew;
        if (e1[s].netid == from) net = e2[s].netid, f = e2[s].facetid;
        else net = e1[s].netid, f = e1[s].facetid;
        u32 pt1 = -1_u32, pt2 = -1_u32, pt1id = -1_u32, pt2id = -1_u32;
        flt_(u32, i, 0, 3) {
          if (vp[s] == faces[f].p.get(i)) pt1 = i, pt1id = s;
          if (vp[net] == faces[f].p.get(i)) pt2 = i, pt2id = net;
        }
        if ((pt1 + 1) % 3 != pt2) swap(pt1, pt2);
        faces.emplace_back(vp, pt2id, pt1id, pid),
          faces[fnew = u32(faces.size() - 1)].id = u32(faces.size() - 1);
        if (ptsid.push_back(vecu()),
            resfnew.push_back(fnew),
            faces[faces[fnew].n[0] = f].n[pt1] = fnew;
            lastf) {
          if (*faces[fnew].p.v == *faces[lastf].p.u)
            faces[fnew].n[1] = lastf, faces[lastf].n[2] = fnew;
          else faces[fnew].n[2] = lastf, faces[lastf].n[1] = fnew;
        } else fstf = fnew;
        lastf = fnew, from = s, s = net;
      }
      if (*faces[fstf].p.v == *faces[lastf].p.u)
        faces[fstf].n[1] = lastf, faces[lastf].n[2] = fstf;
      else faces[fstf].n[2] = lastf, faces[lastf].n[1] = fstf;
      for (resptid.clear(); auto i : resfdel)
        std::ranges::move(ptsid[i], std::back_inserter(resptid)),
          ptsid[i].clear();
      for (auto i : resptid) {
        if (vp[i] == p) continue;
        for (auto j : resfnew)
          if (relation_PlP(faces[j].p, vp[i]) == above_plp) {
            ptsid[j].push_back(i);
            break;
          }
      }
      for (auto i : resfnew) que.push(i);
    }
    idx = snew;
  }
  CEXP FP CR surface_area() {
    if (!is_zero(suf_area)) return suf_area;
    auto f = [&](auto &&f, u32 nf) -> void {
      if (faces[nf].vistime == tm) return;
      for (faces[nf].vistime = tm, suf_area += faces[nf].p.area();
           auto i : faces[nf].n)
        f(f, i);
    };
    return ++tm, f(f, idx), suf_area;
  }
};
}  // namespace tifa_libs::geo
using point = tifa_libs::geo::point3d<f64>;
using cvh = tifa_libs::geo::cvh3d<f64>;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  vec<point> vp(n + 1);
  fle_(u32, i, 1, n) std::cin >> vp[i];
  cvh cvh(vp);
  std::cout << std::fixed << std::setprecision(6) << cvh.surface_area() << '\n';
  return 0;
}
