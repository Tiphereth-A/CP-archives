#include <bits/stdc++.h>
#define CEXP constexpr
#define CEXPE constexpr explicit
#define TPN typename
#define CR const &
#define cT_(...)                                            \
  std::conditional_t<sizeof(__VA_ARGS__) <= sizeof(size_t), \
                     __VA_ARGS__,                           \
                     __VA_ARGS__ CR>
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
using isz = ptrdiff_t;
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using usz = size_t;
using strn = std::string;
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
#define mk(A, T)                                                          \
  mk_(edge_t, A, T) mk_(ptt, A, T) mk_(pt3, A, T) mk_(pt4, A, T)          \
    mk_(vec, A, T) mk_(vvec, A, T) mk_(v3ec, A, T) mk_(vecpt, A, T)       \
      mk_(vvecpt, A, T) mk_(ptvec, A, T) mk_(ptvvec, A, T) mk_(spn, A, T) \
        mk_(itl, A, T)
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
using std::numbers::pi_v;
template <std::floating_point FP>
inline FP eps_v = std::sqrt(std::numeric_limits<FP>::epsilon());
template <std::floating_point FP>
CEXP void set_eps(FP v) {
  eps_v<FP> = v;
}
namespace tifa_libs {
using std::min, std::max, std::swap;
template <class T>
constexpr T abs(T x) {
  return x < 0 ? -x : x;
}
}  // namespace tifa_libs
namespace tifa_libs::graph {
template <bool with_deg = false>
struct alist {
  using weight_type = u32;
  using value_type = vvecu;
  value_type g;
  u32 cnt_arc;
  vecu deg_in, deg_out;
  CEXPE alist(u32 n = 0): g(n), cnt_arc(0) {
    if CEXP (with_deg) deg_in.resize(n), deg_out.resize(n);
  }
  CEXP void add_arc(u32 u, u32 v) {
    g[u].push_back(v), ++cnt_arc;
    if CEXP (with_deg) ++deg_in[v], ++deg_out[u];
  }
};
template <class G>
concept is_alist =
  (std::is_base_of_v<alist<true>, G> || std::is_base_of_v<alist<false>, G>);
}  // namespace tifa_libs::graph
namespace tifa_libs::graph {
struct tree: alist<false> {
  u32 root;
  CEXPE tree(u32 n, u32 root = 0): alist(n), root(root) {}
};
}  // namespace tifa_libs::graph
namespace tifa_libs::graph {
namespace dfs_impl_ {
template <class G, class Fb, class Fp, class Fs, class Fr>
CEXP void dfs_(G CR fg,
               u32 u,
               u32 fa,
               Fb &&init,
               Fp &&pre_dfs,
               Fs &&post_dfs,
               Fr &&before_return) {
  for (init(u, fa); auto v : fg.g[u])
    if CEXP (is_alist<G>) {
      if (v != fa)
        pre_dfs(v, u),
          dfs_(fg,
               v,
               u,
               std::forward<Fb>(init),
               std::forward<Fp>(pre_dfs),
               std::forward<Fs>(post_dfs),
               std::forward<Fr>(before_return)),
          post_dfs(v, u);
    } else if (v.first != fa)
      pre_dfs(v.first, u, v.second),
        dfs_(fg,
             v.first,
             u,
             std::forward<Fb>(init),
             std::forward<Fp>(pre_dfs),
             std::forward<Fs>(post_dfs),
             std::forward<Fr>(before_return)),
        post_dfs(v.first, u, v.second);
  before_return(u, fa);
}
}  // namespace dfs_impl_
template <class G, class Fb, class Fp, class Fs, class Fr>
CEXP void dfs(G CR fg,
              u32 start,
              Fb &&init,
              Fp &&pre_dfs,
              Fs &&post_dfs,
              Fr &&before_return) {
  dfs_impl_::dfs_(fg,
                  start,
                  -1_u32,
                  std::forward<Fb>(init),
                  std::forward<Fp>(pre_dfs),
                  std::forward<Fs>(post_dfs),
                  std::forward<Fr>(before_return));
}
}  // namespace tifa_libs::graph
namespace tifa_libs::graph {
enum tree_dfs_info_mask {
  td_dfn = 1,
  td_sz = 2,
  td_fa = 4,
  td_dep = 8,
  td_maxson = 16,
  td_maxdfn = 32,
  td_euler = 64,
  td_go = 128,
  td_dis = 256
};
template <class G>
struct tree_dfs_info {
  using weight_type = TPN G::weight_type;
  vecu dfn, sz, fa, dep, maxson, maxdfn, euler;
  vvecu go;
  vec<weight_type> dis;
  template <int state>
  CEXP tree_dfs_info &reset_dfs_info(G CR tree) {
    u32 n = (u32)tree.g.size();
    if CEXP (state & td_dfn) dfn = vecu(n);
    if CEXP (state & (td_sz | td_maxson)) sz = vecu(n);
    if CEXP (state & td_fa) fa = vecu(n);
    if CEXP (state & td_dep) dep = vecu(n);
    if CEXP (state & td_maxson) maxson = vecu(n, n);
    if CEXP (state & td_maxdfn) maxdfn = vecu(n);
    if CEXP (state & td_euler) euler = vecu(n);
    if CEXP (state & td_go) go = vvecu(n, vecu(21u, n));
    if CEXP (state & td_dis) dis = vec<weight_type>(n);
    u32 cnt = 0;
    dfs(
      tree,
      tree.root,
      [&](u32 u, u32 f) {
        if CEXP (state & td_dfn) dfn[u] = cnt;
        if CEXP (state & td_euler) euler[cnt] = u;
        if CEXP (state & (td_dfn | td_maxdfn | td_euler)) ++cnt;
        if CEXP (state & (td_sz | td_maxson)) sz[u] = 1;
        if CEXP (state & td_fa) fa[u] = f;
        if CEXP (state & td_go) {
          go[u][0] = f;
          for (u32 i = 1; i <= 20u && go[u][i - 1] < n; i++)
            go[u][i] = go[go[u][i - 1]][i - 1];
        }
      },
      [&](u32 to, u32 u, cT_(weight_type) w = 1) {
        if CEXP (state & td_dep) dep[to] = dep[u] + 1;
        if CEXP (state & td_dis) dis[to] = dis[u] + w;
      },
      [&](u32 to, u32 u, cT_(weight_type) = 1) {
        if CEXP (state & (td_sz | td_maxson)) sz[u] += sz[to];
        if CEXP (state & td_maxson)
          if (maxson[u] == n || sz[to] > sz[maxson[u]]) maxson[u] = to;
      },
      [&](u32 u, u32) {
        if CEXP (state & td_maxdfn) maxdfn[u] = cnt - 1;
      });
    return *this;
  }
};
}  // namespace tifa_libs::graph
namespace tifa_libs::graph {
template <class G, bool need_dfn = false>
CEXP vecu tree_top(G CR tr, tree_dfs_info<G> &info) {
  u32 n = (u32)tr.g.size();
  if (info.maxson.empty()) info.template reset_dfs_info<td_maxson>(tr);
  if CEXP (need_dfn) info.dfn = vecu(n);
  vecu top(n, n);
  u32 cnt = 0;
  auto f = [&](auto &&f, u32 u, u32 top_) -> void {
    if CEXP (need_dfn) info.dfn[u] = cnt++;
    if (top[u] = top_; info.maxson[u] == tr.g.size()) return;
    for (f(f, info.maxson[u], top_); auto v : tr.g[u])
      if CEXP (is_alist<G>) {
        if (top[v] == tr.g.size()) f(f, v, v);
      } else if (top[v.first] == tr.g.size()) f(f, v.first, v.first);
  };
  return f(f, tr.root, tr.root), top;
}
}  // namespace tifa_libs::graph
namespace tifa_libs::ds {
namespace segtree_impl_ {
template <bool enable_tag,
          class T,
          auto op,
          auto e,
          class F,
          auto mapping,
          auto composition,
          auto id>
requires requires(T val, T new_val, F tag, F new_tag) {
  { e() } -> std::same_as<T>;
  { op(val, new_val) } -> std::same_as<T>;
  { mapping(val, tag) } -> std::same_as<T>;
  { composition(tag, new_tag) } -> std::same_as<F>;
  { id() } -> std::same_as<F>;
}
class segtree {
  const T E = e();
  const F ID = id();
  u32 sz, lbn, n;
  vec<T> val;
  vec<F> tag;
  vecb vset;

public:
  template <class V>
  CEXPE segtree(V &&a) {
    reset(std::forward<V>(a));
  }
  CEXPE segtree(u32 n = 0): segtree(vec<T>(n, e())) {}
  template <class V>
  CEXP void reset(V &&a) {
    if (a.empty())
      return sz = lbn = n = 0, val.clear(), tag.clear(), vset.clear();
    sz = (u32)a.size(), lbn = (u32)std::bit_width(sz - 1), n = 1_u32 << lbn;
    if (!n) return;
    if CEXP (val = vec<T>(n * 2, E), std::ranges::copy(a, val.begin() + n);
             enable_tag)
      tag = vec<F>(n, ID), vset = vecb(n);
    for (u32 i = n - 1; i; --i) pushup(i);
  }
  CEXP void update(u32 l, u32 r, cT_(F) v) { upd_set<true>(l, r, v); }
  CEXP void set(u32 l, u32 r, cT_(F) v) { upd_set<false>(l, r, v); }
  CEXP T query(u32 l, u32 r) {
    assert(l <= r && r <= sz);
    if (l == r) return E;
    l += n, r += n;
    for (u32 i = lbn,
             zl = (u32)std::countr_zero(l),
             zr = (u32)std::countr_zero(r),
             ie = (u32)max(1, (i32)min(zl, zr));
         i >= ie;
         --i) {
      if (zl < i) pushdown(l >> i);
      if (zr < i) pushdown((r - 1) >> i);
    }
    T ql = E, qr = E;
    while (l < r) {
      if (l & 1) ql = op(ql, val[l++]);
      if (r & 1) qr = op(val[--r], qr);
      l /= 2, r /= 2;
    }
    return op(ql, qr);
  }
  CEXP void update(u32 x, cT_(F) v) { upd_set<true>(x, v); }
  CEXP void set(u32 x, cT_(T) v) { upd_set<false>(x, v); }
  CEXP T query(u32 x) {
    assert(x < sz);
    x += n;
    for (u32 i = lbn; i; --i) pushdown(x >> i);
    return val[x];
  }
  template <class G>
  requires requires(G check, T val) {
    { check(val) } -> std::same_as<bool>;
  }
  CEXP u32 max_right(u32 l, G &&chk) {
    assert(l <= sz && chk(ID));
    if (l == n) return n;
    l += n;
    for (u32 i = lbn; i; --i) pushdown(l >> i);
    T _ = E;
    do {
      if (!chk(op(_, val[l >>= std::countr_zero(l)]))) {
        while (l < n)
          if (pushdown(l), l *= 2; chk(op(_, val[l]))) _ = op(_, val[l++]);
        return l - n;
      }
      _ = op(_, val[l++]);
    } while (!std::has_single_bit(l));
    return sz;
  }
  template <class G>
  requires requires(G check, T val) {
    { check(val) } -> std::same_as<bool>;
  }
  CEXP u32 min_left(u32 r, G chk) {
    assert(r <= sz && chk(ID));
    if (!r) return 0;
    r += n;
    for (u32 i = lbn; i; --i) pushdown((r - 1) >> i);
    T _ = E;
    do {
      if (!(--r, r >>= std::countr_one(r))) r = 1;
      if (!chk(op(val[r], _))) {
        while (r < n)
          if (pushdown(r), r = r * 2 + 1; chk(op(val[r], _)))
            _ = op(val[r--], _);
        return r + 1 - n;
      }
      _ = op(val[r], _);
    } while (!std::has_single_bit(r));
    return 0;
  }

private:
  CEXP void compose(F &a, cT_(F) b) const {
    a = a == ID ? b : composition(a, b);
  }
  CEXP void pushup(u32 x) { val[x] = op(val[x * 2], val[x * 2 + 1]); }
  template <bool upd>
  CEXP void apply(u32 x, std::conditional_t<upd, cT_(F), cT_(T)> f) {
    if CEXP (upd) {
      if (f == ID) return;
      if CEXP (val[x] = mapping(val[x], f); enable_tag)
        if (x < n) compose(tag[x], f);
    } else if CEXP (val[x] = f; enable_tag)
      if (x < n) tag[x] = ID, vset[x] = 1;
  }
  CEXP void pushdown(u32 x) {
    if CEXP (enable_tag) {
      if (vset[x]) {
        if (val[x * 2] = val[x * 2 + 1] = val[x]; x * 2 < n)
          tag[x * 2] = tag[x * 2 + 1] = ID, vset[x * 2] = vset[x * 2 + 1] = 1;
        vset[x] = 0;
      } else if (tag[x] != ID) {
        if (val[x * 2] = mapping(val[x * 2], tag[x]),
            val[x * 2 + 1] = mapping(val[x * 2 + 1], tag[x]);
            x * 2 < n)
          compose(tag[x * 2], tag[x]), compose(tag[x * 2 + 1], tag[x]);
        tag[x] = ID;
      }
    }
  }
  template <bool upd>
  CEXP void upd_set(u32 l, u32 r, std::conditional_t<upd, cT_(F), cT_(T)> v) {
    assert(l <= r && r <= sz);
    if (l == r) return;
    l += n, r += n;
    u32 zl = (u32)std::countr_zero(l), zr = (u32)std::countr_zero(r),
        zm = min(zl, zr);
    for (u32 i = lbn, ie = (u32)max(1, (i32)zm); i >= ie; --i) {
      if (zl < i) pushdown(l >> i);
      if (zr < i) pushdown((r - 1) >> i);
    }
    u32 l2 = l, r2 = r;
    while (l2 < r2) {
      if (l2 & 1) apply<upd>(l2++, v);
      if (r2 & 1) apply<upd>(--r2, v);
      l2 /= 2, r2 /= 2;
    }
    fle_(u32, i, zm + 1, lbn) {
      if (zl < i) pushup(l >> i);
      if (zr < i) pushup((r - 1) >> i);
    }
  }
  template <bool upd>
  CEXP void upd_set(u32 x, std::conditional_t<upd, cT_(F), cT_(T)> v) {
    assert(x < sz);
    x += n;
    for (u32 i = lbn; i; --i) pushdown(x >> i);
    if CEXP (upd) val[x] = mapping(val[x], v);
    else val[x] = v;
    fle_(u32, i, 1, lbn) pushup(x >> i);
  }
};
}  // namespace segtree_impl_
template <class T,
          auto op,
          auto e,
          class F,
          auto mapping,
          auto composition,
          auto id>
using segtree =
  segtree_impl_::segtree<true, T, op, e, F, mapping, composition, id>;
}  // namespace tifa_libs::ds
namespace tifa_libs::ds {
template <class T,
          auto op,
          auto e,
          class F = T,
          auto mapping = op,
          auto composition = e,
          auto id = e>
class hld {
  segtree<T, op, e, F, mapping, composition, id> t;

public:
  graph::tree &tr;
  graph::tree_dfs_info<graph::tree> info;
  vecu top;
  CEXPE hld(graph::tree &tr): t(), tr(tr), info() {
    info.template reset_dfs_info<graph::td_dep | graph::td_fa>(tr),
      top = graph::tree_top<graph::tree, true>(tr, info);
  }
  CEXP hld(graph::tree &tr, spn<T> a): hld(tr) {
    vec<T> b(a.size());
    flt_(u32, i, 0, (u32)a.size()) b[info.dfn[i]] = a[i];
    build(b);
  }
  CEXP void build(spn<T> a) { t.reset(a); }
  CEXP void chain_update(u32 u, u32 v, cT_(F) f) {
    while (top[u] != top[v]) {
      if (info.dep[top[u]] < info.dep[top[v]]) swap(u, v);
      t.update(info.dfn[top[u]], info.dfn[u] + 1, f), u = info.fa[top[u]];
    }
    if (info.dfn[u] < info.dfn[v]) swap(u, v);
    t.update(info.dfn[v], info.dfn[u] + 1, f);
  }
  CEXP void subtree_update(u32 u, cT_(F) f) {
    t.update(info.dfn[u], info.dfn[u] + info.sz[u], f);
  }
  CEXP void node_update(u32 u, cT_(F) f) { t.update(info.dfn[u], f); }
  CEXP void chain_set(u32 u, u32 v, cT_(T) f) {
    while (top[u] != top[v]) {
      if (info.dep[top[u]] < info.dep[top[v]]) swap(u, v);
      t.set(info.dfn[top[u]], info.dfn[u] + 1, f), u = info.fa[top[u]];
    }
    if (info.dfn[u] < info.dfn[v]) swap(u, v);
    t.set(info.dfn[v], info.dfn[u] + 1, f);
  }
  CEXP void subtree_set(u32 u, cT_(T) f) {
    t.set(info.dfn[u], info.dfn[u] + info.sz[u], f);
  }
  CEXP void node_set(u32 u, cT_(T) f) { t.set(info.dfn[u] + 1, f); }
  CEXP T chain_query(u32 u, u32 v) {
    T ret = e();
    while (top[u] != top[v]) {
      if (info.dep[top[u]] < info.dep[top[v]]) swap(u, v);
      ret = op(ret, t.query(info.dfn[top[u]], info.dfn[u] + 1)),
      u = info.fa[top[u]];
    }
    if (info.dfn[u] < info.dfn[v]) swap(u, v);
    return op(ret, t.query(info.dfn[v], info.dfn[u] + 1));
  }
  CEXP T subtree_query(u32 u) {
    return t.query(info.dfn[u], info.dfn[u] + info.sz[u]);
  }
  CEXP T node_query(u32 u) { return t.query(info.dfn[u]); }
};
}  // namespace tifa_libs::ds
namespace tifa_libs::ds {
namespace segtree_ctor_impl_ {
template <class T>
struct P {
  T v;
  u32 l;
  friend CEXP P operator+(P CR l, P CR r) { return {l.v + r.v, l.l + r.l}; }
  friend std::ostream &operator<<(std::ostream &os, P CR p) {
    return os << p.v;
  }
};
template <class T>
CEXP T set_(cT_(T), cT_(T) y) {
  return y;
}
template <class T>
CEXP T add_(cT_(T) x, cT_(T) y) {
  return x + y;
}
template <class T>
CEXP T min_(cT_(T) x, cT_(T) y) {
  return min(x, y);
}
template <class T>
CEXP T max_(cT_(T) x, cT_(T) y) {
  return max(x, y);
}
template <class T>
CEXP P<T> pset_(P<T> CR x, cT_(T) y) {
  return {x.l * y, x.l};
}
template <class T>
CEXP P<T> padd_(P<T> CR x, cT_(T) y) {
  return {x.v + x.l * y, x.l};
}
template <class T>
CEXP T e_() {
  return T(0);
}
template <class T, T val>
CEXP T v_() {
  return val;
}
template <class T>
CEXP P<T> pe_() {
  return {0, 0};
}
template <class T, T NINF>
CEXP auto segtl_addmax_ctor(spn<T> a) {
  return segtree<T, max_<T>, v_<T, NINF>, T, add_<T>, add_<T>, e_<T>>(a);
}
template <class T, T INF>
CEXP auto segtl_addmin_ctor(spn<T> a) {
  return segtree<T, min_<T>, v_<T, INF>, T, add_<T>, add_<T>, e_<T>>(a);
}
template <class T>
CEXP auto segtl_addsum_ctor(vec<T> CR a) {
  vec<P<T>> b(a.size());
  flt_(u32, i, 0, (u32)a.size()) b[i] = {a[i], 1};
  return segtree<P<T>, add_<P<T>>, pe_<T>, T, padd_<T>, add_<T>, e_<T>>(b);
}
template <class T, T NINF>
CEXP auto segtl_setmax_ctor(spn<T> a) {
  return segtree<T, max_<T>, v_<T, NINF>, T, set_<T>, set_<T>, v_<T, NINF>>(a);
}
template <class T, T INF>
CEXP auto segtl_setmin_ctor(spn<T> a) {
  return segtree<T, min_<T>, v_<T, INF>, T, set_<T>, set_<T>, v_<T, INF>>(a);
}
template <class T, T DEF_VAL>
CEXP auto segtl_setsum_ctor(spn<T> a) {
  vec<P<T>> b(a.size());
  flt_(u32, i, 0, (u32)a.size()) b[i] = {a[i], 1};
  return segtree<P<T>,
                 add_<P<T>>,
                 pe_<T>,
                 T,
                 pset_<T>,
                 set_<T>,
                 v_<T, DEF_VAL>>(b);
}
}  // namespace segtree_ctor_impl_
using segtree_ctor_impl_::segtl_addmax_ctor,
  segtree_ctor_impl_::segtl_addmin_ctor, segtree_ctor_impl_::segtl_addsum_ctor;
using segtree_ctor_impl_::segtl_setmax_ctor,
  segtree_ctor_impl_::segtl_setmin_ctor, segtree_ctor_impl_::segtl_setsum_ctor;
}  // namespace tifa_libs::ds
using namespace std;
using T = tifa_libs::ds::segtree_ctor_impl_::P<u64>;
T comp(T x, u32 y) { return {y ? x.l - x.v : x.v, x.l}; }
u32 bxor(u32 x, u32 y) { return x ^ y; }
u32 id() { return 0; }
void solve() {
  u32 n;
  cin >> n;
  tifa_libs::graph::tree t(n);
  flt_(u32, i, 1, n) {
    u32 x;
    cin >> x;
    --x;
    t.add_arc(x, i);
    t.add_arc(i, x);
  }
  vec<T> _(n);
  flt_(u32, i, 0, n) {
    u32 x;
    cin >> x;
    _[i] = {x, 1};
  }
  tifa_libs::ds::hld<T,
                     tifa_libs::ds::segtree_ctor_impl_::add_<T>,
                     tifa_libs::ds::segtree_ctor_impl_::pe_<u64>,
                     u32,
                     comp,
                     bxor,
                     id>
    tr(t, _);
  u32 m;
  cin >> m;
  while (m--) {
    strn op;
    u32 x;
    cin >> op >> x;
    if (op == "pow") tr.subtree_update(x - 1, 1);
    else cout << tr.subtree_query(x - 1) << '\n';
  }
}
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  solve();
  return 0;
}
