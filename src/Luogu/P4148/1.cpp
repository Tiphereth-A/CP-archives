#include <bits/extc++.h>
#define CEXP constexpr
#define CEXPE constexpr explicit
#define CR const &
#define TPN typename
#define NE noexcept
#define CNE const noexcept
#define cT_(...)                                                \
  std::conditional_t<sizeof(__VA_ARGS__) <= sizeof(size_t) * 2, \
                     __VA_ARGS__,                               \
                     __VA_ARGS__ CR>
#define flt_(T, i, l, r, ...) \
  for (T i = (l), i##e = (r)__VA_OPT__(, ) __VA_ARGS__; i < i##e; ++i)
#undef assert
#define assert(x) 42
#define mk_(w, t) \
  using w = t;    \
  CEXP w operator""_##w(unsigned long long x) NE { return (w)x; }
mk_(i8, int8_t) mk_(u8, uint8_t) mk_(i16, int16_t) mk_(u16, uint16_t)
  mk_(i32, int32_t) mk_(u32, uint32_t) mk_(i64, int64_t) mk_(u64, uint64_t)
    mk_(isz, ptrdiff_t) mk_(usz, size_t);
#undef mk_
using i128 = __int128_t;
using u128 = __uint128_t;
using f128 = long double;
using strn = std::string;
using strnv = std::string_view;
using std::numbers::pi_v;
template <std::floating_point FP>
inline FP eps_v = std::sqrt(std::numeric_limits<FP>::epsilon());
template <std::floating_point FP>
CEXP void set_eps(FP v) NE {
  eps_v<FP> = v;
}
CEXP u32 TIME = ((__TIME__[0] & 15) << 20) | ((__TIME__[1] & 15) << 16) |
                ((__TIME__[3] & 15) << 12) | ((__TIME__[4] & 15) << 8) |
                ((__TIME__[6] & 15) << 4) | (__TIME__[7] & 15);
template <class T>
struct chash {
  CEXP static u64 C = u64(pi_v<f128> * 2e18) | 71;
  CEXP u64 operator()(T x) CNE {
    return __builtin_bswap64(((u64)x ^ TIME) * C);
  }
};
template <class T>
using ptt = std::pair<T, T>;
template <class T>
struct edge_t {
  T w;
  u32 u, v;
  CEXP auto operator<=>(edge_t CR) const = default;
};
template <class T>
struct pt3 {
  T _0, _1, _2;
  CEXP auto operator<=>(pt3 CR) const = default;
};
template <class T>
struct pt4 {
  T _0, _1, _2, _3;
  CEXP auto operator<=>(pt4 CR) const = default;
};
template <class T>
using alc = std::pmr::polymorphic_allocator<T>;
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
template <class T, usz N>
using arr = std::array<T, N>;
using std::set, std::map;
#define mk_(V, A, T) using V##A = V<T>;
#define mk(A, T)                                                          \
  mk_(edge_t, A, T) mk_(ptt, A, T) mk_(pt3, A, T) mk_(pt4, A, T)          \
    mk_(vec, A, T) mk_(vvec, A, T) mk_(v3ec, A, T) mk_(vecpt, A, T)       \
      mk_(vvecpt, A, T) mk_(ptvec, A, T) mk_(ptvvec, A, T) mk_(spn, A, T) \
        mk_(itl, A, T)
mk(b, bool) mk(i, i32) mk(u, u32) mk(ii, i64) mk(uu, u64);
#undef mk
#undef mk_
inline const auto fn_0 = [](auto &&...) NE {};
using namespace std::ranges;
using namespace std::literals;
namespace tifa_libs {
template <class T>
CEXP T abs(T x) NE {
  return x < 0 ? -x : x;
}
}  // namespace tifa_libs
namespace tifa_libs {
template <class T>
concept char_c = std::same_as<T, char> || std::same_as<T, signed char> ||
                 std::same_as<T, unsigned char>;
template <class T>
concept s128_c = std::same_as<T, __int128_t> || std::same_as<T, __int128>;
template <class T>
concept u128_c =
  std::same_as<T, __uint128_t> || std::same_as<T, unsigned __int128>;
template <class T>
concept i128_c = s128_c<T> || u128_c<T>;
template <class T>
concept imost64_c = std::integral<T> && sizeof(T) * __CHAR_BIT__ <= 64;
template <class T>
concept smost64_c = imost64_c<T> && std::signed_integral<T>;
template <class T>
concept umost64_c = imost64_c<T> && std::unsigned_integral<T>;
template <class T>
concept int_c = i128_c<T> || imost64_c<T>;
template <class T>
concept sint_c = s128_c<T> || smost64_c<T>;
template <class T>
concept uint_c = u128_c<T> || umost64_c<T>;
template <class T>
concept arithm_c = std::is_arithmetic_v<T> || int_c<T>;
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
concept container_c = range<T> && !std::is_array_v<std::remove_cvref_t<T>> &&
                      !std::same_as<std::remove_cvref_t<T>, strn> &&
                      !std::same_as<std::remove_cvref_t<T>, strnv>;
template <class T> concept sparse_graph_c = requires(T g) { g.cnt_arc; g.deg_in; g.deg_out; g.size(); g.foreach(0, fn_0); } && (requires(T g) { g.add_arc(0, 0); g.add_edge(0, 0); } || requires(T g) { g.add_arc(0, 0, {}); g.add_edge(0, 0, {}); });
template <class T>
concept alist_c = sparse_graph_c<T> && requires(T g) {
  { g[0] } -> common_range;
  g.build();
};
template <class T>
concept eog_c = sparse_graph_c<T> && requires(T g) {
  g.head;
  g.e;
  g.pop_startwith(0);
};
template <class T>
concept tree_c = alist_c<T> && requires(T g) { g.root; };
template <class T>
concept sparse_graphw_c = sparse_graph_c<T> && !std::is_void_v<TPN T::w_t> &&
                          requires(T g, TPN T::w_t w) {
                            g.add_arc(0, 0, w);
                            g.add_edge(0, 0, w);
                          };
template <class T> concept alistw_c = alist_c<T> && sparse_graphw_c<T> && (requires(T g) { g[0].begin()->first; g[0].begin()->second; } || requires(T g) { g[0].begin()->to; g[0].begin()->cost; });
template <class T>
concept eogw_c = eog_c<T> && sparse_graphw_c<T> && requires(T g) {
  g[0].to;
  g[0].w;
  g[0].nxt;
};
template <class T>
concept treew_c = tree_c<T> && alistw_c<T>;
template <class P>
concept tp_ds_c = requires(P p) {
  p->ch;
  std::is_array_v<decltype(p->ch)>;
  std::rank_v<decltype(p->ch)> == 1;
};
template <class P>
concept tp2_ds_c =
  tp_ds_c<P> && std::extent_v<decltype(std::declval<P>()->ch)> == 2;
template <class T>
concept istream_c =
  std::derived_from<T, std::istream> || requires(T is, T &(*func)(T &)) {
    { is >> func } -> std::same_as<T &>;
  };
template <class T>
concept ostream_c =
  std::derived_from<T, std::ostream> || requires(T os, T &(*func)(T &)) {
    { os << func } -> std::same_as<T &>;
  };
template <class T>
concept dsu_c = requires(T dsu, u32 x, u32 y) {
  { dsu.find(x) } -> std::same_as<i32>;
  { dsu.size() } -> std::same_as<u32>;
  { dsu.size(x) } -> std::same_as<u32>;
  { dsu.same(x, y) } -> std::same_as<bool>;
  { dsu.merge(x, y) } -> std::same_as<bool>;
};
template <class T>
struct to_sint: std::make_signed<T> {};
template <>
struct to_sint<u128> {
  using type = i128;
};
template <>
struct to_sint<i128> {
  using type = i128;
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
template <class T>
using to_uint_t = TPN to_uint<T>::type;
template <arithm_c T>
struct to_bigger: std::make_unsigned<T> {};
#define _2(w, ww)          \
  template <>              \
  struct to_bigger<i##w> { \
    using type = i##ww;    \
  };                       \
  template <>              \
  struct to_bigger<u##w> { \
    using type = u##ww;    \
  }
#define _3(w, ww)          \
  _2(w, ww);               \
  template <>              \
  struct to_bigger<f##w> { \
    using type = f##ww;    \
  }
_2(8, 16);
_2(16, 32);
#undef _3
#undef _2
template <class, template <class...> class>
CEXP bool specialized_from_v = false;
template <template <class...> class T, class... Args>
CEXP bool specialized_from_v<T<Args...>, T> = true;
static_assert(specialized_from_v<vecu, std::vector>);
template <arithm_c T>
CEXP T inf_v = [] {
  if CEXP (sint_c<T>) return T(to_uint_t<T>(-1) / 4 - 1);
  else if CEXP (uint_c<T>) return T(-1) / 2 - 1;
  else return std::numeric_limits<T>::max() / 2 - 1;
}();
}  // namespace tifa_libs
namespace tifa_libs::ds {
template <tp2_ds_c pointer, class F>
requires requires(pointer p, F &&f) { f(p); }
CEXP void pre_order(pointer p, F &&f) NE {
  if (p)
    f(p), pre_order(p->ch[0], std::forward<F>(f)),
      pre_order(p->ch[1], std::forward<F>(f));
}
template <tp2_ds_c pointer, class F>
requires requires(pointer p, F f) { f(p); }
CEXP void in_order(pointer p, F &&f) NE {
  if (p)
    in_order(p->ch[0], std::forward<F>(f)), f(p),
      in_order(p->ch[1], std::forward<F>(f));
}
template <tp2_ds_c pointer, class F>
requires requires(pointer p, F f) { f(p); }
CEXP void post_order(pointer p, F &&f) NE {
  if (p)
    post_order(p->ch[0], std::forward<F>(f)),
      post_order(p->ch[1], std::forward<F>(f)), f(p);
}
template <tp_ds_c pointer, class F>
requires requires(pointer p, u32 level, F f) { f(p, level); }
CEXP void level_order(pointer p, F &&f) NE {
  if (!p) return;
  u32 level = 0;
  std::queue<pointer> q({p});
  while (!q.empty()) {
    flt_(u32, i, 0, (u32)q.size()) {
      auto now = q.front();
      q.pop(), f(now, level);
      for (auto &&s : now->ch) q.push(s);
    }
    ++level;
  }
}
template <tp_ds_c pointer, class Alloc>
CEXP void dealloc_subtree(pointer p, Alloc &alloc) NE {
  if (!p) return;
  for (auto &&s : p->ch) dealloc_subtree(s, alloc);
  alloc.deallocate(p, 1);
}
template <tp_ds_c pointer>
CEXP pointer most(pointer p, bool dir) NE {
  if (!p) return nullptr;
  while (p->ch[dir]) p = p->ch[dir];
  return p;
}
template <tp2_ds_c pointer>
CEXP auto leftmost(pointer p) NE {
  return most(p, 0);
}
template <tp2_ds_c pointer>
CEXP auto rightmost(pointer p) NE {
  return most(p, 1);
}
}  // namespace tifa_libs::ds
namespace tifa_libs::ds {
template <class T, auto op, arithm_c Coord = i32, u32 K = 2>
class KDtree {
  static_assert(K);
  struct TIFA;

public:
  using point = arr<Coord, K>;

private:
  using pointer = TIFA *;
  using const_pointer = const TIFA *;
  struct TIFA {
    pointer ch[2];
    T sum, val;
    point min, max, coord;
    template <u32 k>
    requires(k < K)
    static CEXP bool cmp(const_pointer l, const_pointer r) {
      return l->coord[k] < r->coord[k];
    }
  };
  const T E;
  const u32 B;
  u32 cnt;
  CEXP pointer newnode(cT_(point) p, cT_(T) val) {
    pointer x = alloc.allocate(1);
    x->ch[0] = x->ch[1] = nullptr;
    x->sum = x->val = val;
    flt_(u32, i, 0, K) x->min[i] = x->max[i] = x->coord[i] = p[i];
    return x;
  }
  CEXP void pushup(pointer x) NE {
    auto [l, r] = x->ch;
    x->sum = x->val;
    if (l) {
      x->sum = op(x->sum, l->sum);
      flt_(u32, i, 0, K) x->max[i] = max(l->max[i], x->max[i]);
      flt_(u32, i, 0, K) x->min[i] = min(l->min[i], x->min[i]);
    }
    if (r) {
      x->sum = op(x->sum, r->sum);
      flt_(u32, i, 0, K) x->max[i] = max(r->max[i], x->max[i]);
      flt_(u32, i, 0, K) x->min[i] = min(r->min[i], x->min[i]);
    }
  }
  template <u32 k>
  requires(k < K)
  CEXP void build(pointer &x, vec<pointer> &h, u32 l, u32 r) NE {
    if (l >= r) return;
    u32 mid = l + (r - l) / 2;
    nth_element(
      h.begin() + l, h.begin() + mid, h.begin() + r, TIFA::template cmp<k>);
    x = h[mid], x->sum = x->val;
    flt_(u32, i, 0, K) x->min[i] = x->max[i] = x->coord[i];
    build<(k + 1) % K>(x->ch[0], h, l, mid),
      build<(k + 1) % K>(x->ch[1], h, mid + 1, r);
    pushup(x);
  }
  CEXP void rebuild(pointer &x) NE {
    vec<pointer> h;
    auto flatten = [&](auto &&f, pointer &x) -> void {
      if (!x) return;
      h.push_back(x), f(f, x->ch[0]), f(f, x->ch[1]), x = nullptr;
    };
    flatten(flatten, x), build<0>(x, h, 0, (u32)h.size());
  }
  template <u32 k>
  requires(k < K)
  CEXP bool insert_(pointer &x, cT_(point) p, cT_(T) val) NE {
    if (!x) {
      x = newnode(p, val);
      return true;
    }
    bool f = false;
    if (p == x->coord) x->val = op(x->val, val), x->sum = op(x->sum, val);
    else f = insert_<(k + 1) % K>(x->ch[p[k] >= x->coord[k]], p, val);
    pushup(x);
    return f;
  }
  CEXP bool check_range(const_pointer x, cT_(point) L, cT_(point) R) CNE {
    flt_(u32, i, 0, K) if (x->min[i] < L[i] || R[i] < x->max[i]) return false;
    return true;
  }
  CEXP bool check_point(const_pointer x, cT_(point) L, cT_(point) R) CNE {
    flt_(u32, i, 0, K) if (x->coord[i] < L[i] ||
                           R[i] < x->coord[i]) return false;
    return true;
  }
  CEXP bool check(const_pointer x, cT_(point) L, cT_(point) R) CNE {
    if (!x) return false;
    flt_(u32, i, 0, K) if (R[i] < x->min[i] || x->max[i] < L[i]) return false;
    return true;
  }
  CEXP void query_(const_pointer x, cT_(point) L, cT_(point) R, T &ans) CNE {
    if (!x) return;
    if (check_range(x, L, R)) {
      ans = op(ans, x->sum);
      return;
    }
    if (check_point(x, L, R)) ans = op(ans, x->val);
    if (check(x->ch[0], L, R)) query_(x->ch[0], L, R, ans);
    if (check(x->ch[1], L, R)) query_(x->ch[1], L, R, ans);
  }

public:
  pointer root;
  CEXPE KDtree(u32 rebuild_threshold, cT_(T) e = T{}) NE:
    E{e},
    B{rebuild_threshold},
    cnt{0},
    root{nullptr} {
    assert(rebuild_threshold > 1);
  }
  CEXP ~KDtree() NE { dealloc_subtree(root, alloc); }
  CEXP void insert(cT_(point) coord, cT_(T) val) NE {
    if ((cnt += insert_<0>(root, coord, val)) == B) cnt = 0, rebuild(root);
  }
  CEXP T query(cT_(point) L, cT_(point) R) CNE {
    T ans{E};
    query_(root, L, R, ans);
    return ans;
  }

private:
  alc<TIFA> alloc;
};
}  // namespace tifa_libs::ds
int op(int x, int y) { return x + y; }
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  tifa_libs::ds::KDtree<int, op> kdt(1897);
  using point_t = decltype(kdt)::point;
  u32 n;
  std::cin >> n;
  int ans = 0;
  point_t p1, p2;
  while (true) {
    u32 opt;
    std::cin >> opt;
    if (opt == 1) {
      int A;
      std::cin >> p1[0] >> p1[1] >> A;
      p1[0] ^= ans, p1[1] ^= ans, A ^= ans;
      kdt.insert(p1, A);
    } else if (opt == 2) {
      std::cin >> p1[0] >> p1[1] >> p2[0] >> p2[1];
      p1[0] ^= ans, p1[1] ^= ans, p2[0] ^= ans, p2[1] ^= ans;
      std::cout << (ans = kdt.query(p1, p2)) << '\n';
    } else return 0;
  }
}
