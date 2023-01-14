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
namespace tifa_libs::graph {
template <class T>
struct blossomw {
  struct TIFA {
    u32 u, v;
    T w;
  };
  vvec<TIFA> g;
  u32 n, nx;
  vec<T> lab;
  vecu match, slack, st, par, s, aux;
  vvecu flo_from, flo;
  std::queue<u32> q;
  blossomw(u32 n) { init(n); }
  void init(u32 n_) {
    n = n_, g = vvec<TIFA>(n * 2 + 1, vec<TIFA>(n * 2 + 1));
    lab = vec<T>(n * 2 + 1), match = vecu(n * 2 + 1), slack = vecu(n * 2 + 1),
    st = vecu(n * 2 + 1);
    par = vecu(n * 2 + 1), s = vecu(n * 2 + 1), aux = vecu(n * 2 + 1);
    flo_from = vvecu(n * 2 + 1, vecu(n + 1)), flo = vvecu(n * 2 + 1);
    fle_(u32, u, 1, n) fle_(u32, v, 1, n) g[u][v] = {u, v, 0};
  }
  CEXP void add_edge(u32 u, u32 v, T w) { g[u][v].w = g[v][u].w = w; }
  auto operator()(T inf = std::numeric_limits<T>::max()) {
    nx = n, st[0] = 0;
    fle_(u32, i, 1, 2 * n) aux[i] = 0;
    fle_(u32, i, 1, n) match[i] = 0, st[i] = i, flo[i].clear();
    T wmax = 0;
    fle_(u32, u, 1, n) fle_(u32, v, 1, n) flo_from[u][v] = (u == v ? u : 0),
                                          wmax = max(wmax, g[u][v].w);
    fle_(u32, u, 1, n) lab[u] = wmax;
    while (matching(inf));
    vec<std::tuple<u32, u32, T>> ans;
    fle_(u32, u, 1, n) if (match[u] && match[u] < u)
      ans.emplace_back(u, match[u], g[u][match[u]].w);
    return ans;
  }

private:
  CEXP T e_delta(TIFA CR e) { return lab[e.u] + lab[e.v] - g[e.u][e.v].w * 2; }
  CEXP void upd_slack(u32 u, u32 x) {
    if (!slack[x] || e_delta(g[u][x]) < e_delta(g[slack[x]][x])) slack[x] = u;
  }
  CEXP void set_slack(u32 x) {
    slack[x] = 0;
    fle_(u32, u, 1, n) if (g[u][x].w > 0 && st[u] != x && s[st[u]] == 0)
      upd_slack(u, x);
  }
  void q_push(u32 x) {
    if (x <= n) q.push(x);
    else
      for (auto t : flo[x]) q_push(t);
  }
  CEXP void set_st(u32 x, u32 b) {
    if (st[x] = b; x > n)
      for (auto t : flo[x]) set_st(t, b);
  }
  CEXP u32 get_pr(u32 b, u32 xr) {
    if (u32 pr = u32(std::ranges::find(flo[b], xr) - flo[b].begin()); pr & 1) {
      std::reverse(flo[b].begin() + 1, flo[b].end());
      return u32(flo[b].size() - pr);
    } else return pr;
  }
  CEXP void set_match(u32 u, u32 v) {
    auto [eu, ev, _] = g[u][v];
    if (match[u] = ev; u <= n) return;
    u32 xr = flo_from[u][eu], pr = get_pr(u, xr);
    flt_(u32, i, 0, pr) set_match(flo[u][i], flo[u][i ^ 1]);
    set_match(xr, v),
      std::rotate(flo[u].begin(), flo[u].begin() + pr, flo[u].end());
  }
  CEXP void augment(u32 u, u32 v) {
    while (1) {
      u32 xnv = st[match[u]];
      if (set_match(u, v); !xnv) return;
      set_match(xnv, st[par[xnv]]), u = st[par[xnv]], v = xnv;
    }
  }
  u32 lca(u32 u, u32 v) {
    static u32 t = 0;
    for (++t; u || v; swap(u, v)) {
      if (!u) continue;
      if (aux[u] == t) return u;
      if (aux[u] = t; (u = st[match[u]])) u = st[par[u]];
    }
    return 0;
  }
  CEXP void add_blossom(u32 u, u32 anc, u32 v) {
    u32 b = n + 1;
    while (b <= nx && st[b]) ++b;
    if (b > nx) ++nx;
    lab[b] = s[b] = 0, match[b] = match[anc], flo[b] = {anc};
    auto blossom = [&](u32 x) {
      for (u32 y; x != anc; x = st[par[y]])
        flo[b].push_back(x), flo[b].push_back(y = st[match[x]]), q_push(y);
    };
    blossom(u), std::reverse(flo[b].begin() + 1, flo[b].end()), blossom(v),
      set_st(b, b);
    fle_(u32, x, 1, nx) g[b][x].w = g[x][b].w = 0;
    fle_(u32, x, 1, n) flo_from[b][x] = 0;
    for (auto xs : flo[b]) {
      fle_(u32, x, 1, nx) if (g[b][x].w == 0 ||
                              e_delta(g[xs][x]) < e_delta(g[b][x]))
        g[b][x] = g[xs][x],
        g[x][b] = g[x][xs];
      fle_(u32, x, 1, n) if (flo_from[xs][x]) flo_from[b][x] = xs;
    }
    set_slack(b);
  }
  CEXP void expand_blossom(u32 b) {
    for (auto t : flo[b]) set_st(t, t);
    const u32 xr = flo_from[b][g[b][par[b]].u], pr = get_pr(b, xr);
    for (u32 i = 0; i < pr; i += 2) {
      u32 xs = flo[b][i], xns = flo[b][i + 1];
      par[xs] = g[xns][xs].u, s[xs] = 1, s[xns] = slack[xs] = slack[xns] = 0,
      q_push(xns);
    }
    s[xr] = 1, par[xr] = par[b];
    flt_(u32, i, pr + 1, (u32)flo[b].size()) {
      u32 xs = flo[b][i];
      s[xs] = -1_u32, set_slack(xs);
    }
    st[b] = 0;
  }
  bool on_found_edge(TIFA CR e) {
    const u32 u = st[e.u], v = st[e.v];
    if (!~s[v]) {
      par[v] = e.u, s[v] = 1, slack[v] = 0;
      u32 nu = st[match[v]];
      s[nu] = slack[nu] = 0, q_push(nu);
    } else if (!s[v]) {
      if (u32 anc = lca(u, v); !anc) return augment(u, v), augment(v, u), 1;
      else add_blossom(u, anc, v);
    }
    return 0;
  }
  bool matching(T inf) {
    q = std::queue<u32>();
    fle_(u32, x, 1, nx) if (s[x] = -1_u32, slack[x] = 0;
                            st[x] == x && !match[x]) par[x] = s[x] = 0,
                                                     q_push(x);
    if (q.empty()) return 0;
    while (1) {
      while (!q.empty()) {
        const u32 u = q.front();
        if (q.pop(); s[st[u]] == 1) continue;
        fle_(u32, v, 1, n) if (g[u][v].w > 0 && st[u] != st[v]) {
          if (!e_delta(g[u][v])) {
            if (on_found_edge(g[u][v])) return 1;
          } else upd_slack(u, st[v]);
        }
      }
      T d = inf;
      fle_(u32, b, n + 1, nx) if (st[b] == b && s[b] == 1) d =
        min(d, lab[b] / 2);
      fle_(u32, x, 1, nx) if (st[x] == x && slack[x]) {
        if (!~s[x]) d = min(d, e_delta(g[slack[x]][x]));
        else if (!s[x]) d = min(d, e_delta(g[slack[x]][x]) / 2);
      }
      fle_(u32, u, 1, n) {
        if (!s[st[u]]) {
          if (lab[u] <= d) return 0;
          lab[u] -= d;
        } else if (s[st[u]] == 1) lab[u] += d;
      }
      fle_(u32, b, n + 1, nx) if (st[b] == b && ~s[b]) lab[b] +=
        (!s[b] ? 1 : -1) * d * 2;
      q = std::queue<u32>();
      fle_(
        u32,
        x,
        1,
        nx) if (st[x] == x && slack[x] && st[slack[x]] != x &&
                !e_delta(
                  g[slack[x]][x])) if (on_found_edge(g[slack[x]][x])) return 1;
      fle_(u32, b, n + 1, nx) if (st[b] == b && s[b] == 1 && !lab[b])
        expand_blossom(b);
    }
    return 0;
  }
};
}  // namespace tifa_libs::graph
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
template <tifa_libs::container_c T>
std::istream &operator>>(std::istream &is, T &x) {
  for (auto &i : x) is >> i;
  return is;
}
template <tifa_libs::container_c T>
std::ostream &operator<<(std::ostream &os, T CR x) {
  if (x.begin() == x.end()) return os;
  auto it = x.begin();
  for (os << *it++; it != x.end(); ++it) os << ' ' << *it;
  return os;
}
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  tifa_libs::graph::blossomw<u64> bl(n + 1);
  for (u32 i = 0, x, y; i < m; ++i) {
    u64 w;
    std::cin >> x >> y >> w;
    bl.add_edge(x, y, w);
  }
  auto me = bl();
  u64 sumw = 0;
  vecu ans(n);
  for (auto [u, v, w] : me) ans[u - 1] = v, ans[v - 1] = u, sumw += w;
  std::cout << sumw << '\n';
  std::cout << ans << '\n';
  return 0;
}
