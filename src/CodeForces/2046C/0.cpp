#include <bits/extc++.h>
#define CEXP constexpr
#define TPN typename
#define CR const &
#undef assert
#define assert(x) 42
#define mk_(w, t) \
  using w = t;    \
  CEXP w operator""_##w(unsigned long long x) { return (w)x; }
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
CEXP void set_eps(FP v) {
  eps_v<FP> = v;
}
CEXP u32 TIME = ((__TIME__[0] & 15) << 20) | ((__TIME__[1] & 15) << 16) |
                ((__TIME__[3] & 15) << 12) | ((__TIME__[4] & 15) << 8) |
                ((__TIME__[6] & 15) << 4) | (__TIME__[7] & 15);
template <class T>
struct chash {
  CEXP static u64 C = u64(pi_v<f128> * 2e18) | 71;
  CEXP u64 operator()(T x) const {
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
using namespace std::literals;
namespace tifa_libs {
using std::min, std::max, std::swap;
template <class T>
CEXP T abs(T x) {
  return x < 0 ? -x : x;
}
}  // namespace tifa_libs
namespace tifa_libs::ds {
struct ostree_tag_base {
  template <class pointer>
  static CEXP u32 size(pointer p) {
    return p ? p->sz : 0;
  }
  template <class pointer>
  static CEXP u32 count(pointer p) {
    return p ? p->sz - size(p->ch[0]) - size(p->ch[1]) : 0;
  }
  template <class pointer>
  static CEXP void modify_size(pointer begin, i32 v, pointer end = nullptr) {
    while (begin != end) begin->sz += (u32)v, begin = begin->fa;
  }
  template <class pointer, class F>
  requires requires(pointer p, F &&f) { f(p); }
  static CEXP void pre_order(pointer p, F &&f) {
    if (p)
      f(p), pre_order(p->ch[0], std::forward<F>(f)),
        pre_order(p->ch[1], std::forward<F>(f));
  }
  template <class pointer, class F>
  requires requires(pointer p, F f) { f(p); }
  static CEXP void in_order(pointer p, F &&f) {
    if (p)
      in_order(p->ch[0], std::forward<F>(f)), f(p),
        in_order(p->ch[1], std::forward<F>(f));
  }
  template <class pointer, class F>
  requires requires(pointer p, F f) { f(p); }
  static CEXP void post_order(pointer p, F &&f) {
    if (p)
      post_order(p->ch[0], std::forward<F>(f)),
        post_order(p->ch[1], std::forward<F>(f)), f(p);
  }
  template <class pointer>
  static CEXP pointer most(pointer p, bool dir) {
    if (!p) return nullptr;
    while (p->ch[dir]) p = p->ch[dir];
    return p;
  }
  template <class pointer>
  static CEXP pointer neighbour(pointer p, bool dir) {
    if (!p) return nullptr;
    if (p->ch[dir]) return most(p->ch[dir], !dir);
    while (p && p->fa && p->child_dir() == dir) p = p->fa;
    return p ? p->fa : nullptr;
  }
  template <class pointer>
  static CEXP auto leftmost(pointer p) {
    return most(p, 0);
  }
  template <class pointer>
  static CEXP auto rightmost(pointer p) {
    return most(p, 1);
  }
  template <class pointer>
  static CEXP auto prev(pointer p) {
    return neighbour(p, 0);
  }
  template <class pointer>
  static CEXP auto next(pointer p) {
    return neighbour(p, 1);
  }
  template <class pointer>
  static CEXP pointer rotate(pointer &root, pointer p, bool dir) {
    auto g = p->fa, s = p->ch[!dir];
    u32 psz = p->sz, ssz = s->sz;
    s->sz = psz, p->sz += size(s->ch[dir]) - ssz;
    auto c = s->ch[dir];
    if (c) c->fa = p;
    p->ch[!dir] = c, s->ch[dir] = p, p->fa = s, s->fa = g;
    return (g ? g->ch[p == g->ch[1]] : root) = s;
  }
};
struct bst_tag: ostree_tag_base {
  template <class pointer>
  static CEXP void insert_leaf(pointer &root, pointer p, pointer n, bool dir) {
    if (!p) return void(root = n);
    p->ch[dir] = n, n->fa = p;
  }
  template <class pointer>
  static CEXP void erase_branch_leaf(pointer &root, pointer n) {
    auto p = n->fa, s = n->ch[0] ? n->ch[0] : n->ch[1];
    if (s) s->fa = p;
    if (!p) return void(root = s);
    p->ch[n->child_dir()] = s;
  }
};
template <class T, class K>
struct ostree_node_t {};
template <class K>
struct ostree_node_t<bst_tag, K> {
  ostree_node_t *fa, *ch[2];
  K data;
  u32 sz;
  CEXP bool child_dir() const { return this == fa->ch[1]; }
};
template <class K,
          std::derived_from<ostree_tag_base> tag_t,
          class Comp = std::less<K>,
          template <class> class Alloc = std::pmr::polymorphic_allocator>
requires requires(ostree_node_t<tag_t, K> *&root,
                  ostree_node_t<tag_t, K> n,
                  tag_t tag,
                  bool dir) {
  n.fa->ch[0]->ch[1]->data;
  n.sz;
  { n.child_dir() } -> std::same_as<bool>;
  { tag.size(&n) } -> std::same_as<u32>;
  tag.insert_leaf(root, &n, &n, dir);
  tag.erase_branch_leaf(root, &n);
}
struct ostree: tag_t {
  using node_t = ostree_node_t<tag_t, K>;
  using pointer = node_t *;
  using const_pointer = const node_t *;
  static constexpr Comp compare{};
  pointer root;
  CEXP ostree(): tag_t(), root{nullptr} {}
  CEXP ~ostree() {
    tag_t::post_order(root, [this](auto it) { alloc.deallocate(it, 1); });
  }
  CEXP u32 size() const { return tag_t::size(root); }
  CEXP pointer lower_bound(const K &key) const {
    const_pointer now = root, ans = nullptr;
    while (now) {
      if (!compare(now->data, key)) ans = now, now = now->ch[0];
      else now = now->ch[1];
    }
    return (pointer)ans;
  }
  CEXP pointer upper_bound(const K &key) const {
    const_pointer now = root, ans = nullptr;
    while (now) {
      if (compare(key, now->data)) ans = now, now = now->ch[0];
      else now = now->ch[1];
    }
    return (pointer)ans;
  }
  CEXP pointer find(const K &key) const {
    auto p = lower_bound(key);
    return (!p || compare(p->data, key) || compare(key, p->data)) ? nullptr : p;
  }
  CEXP u32 order_of_key(const K &key) const {
    u32 ans = 0;
    auto now = root;
    while (now) {
      if (!compare(now->data, key)) now = now->ch[0];
      else ans += tag_t::size(now->ch[0]) + tag_t::count(now), now = now->ch[1];
    }
    return ans;
  }
  CEXP const_pointer find_by_order(u32 order) const {
    const_pointer now = root, ans = nullptr;
    while (now && now->sz >= order)
      if (auto lsz = tag_t::size(now->ch[0]), cnt = tag_t::count(now);
          order < lsz)
        now = now->ch[0];
      else {
        if (ans = now; order < lsz + cnt) break;
        now = now->ch[1], order -= lsz + cnt;
      }
    return ans;
  }
  CEXP const_pointer insert(const K &data) {
    pointer now = root, p = nullptr;
    bool dir = 0;
    while (now)
      if (dir = compare((p = now)->data, data), now = now->ch[dir];
          !dir && !compare(data, p->data))
        return tag_t::modify_size(p, 1), p;
    pointer n = alloc.allocate(1);
    n->fa = n->ch[0] = n->ch[1] = nullptr, n->data = data, n->sz = 1;
    return tag_t::modify_size(p, 1), tag_t::insert_leaf(root, p, n, dir), n;
  }
  CEXP bool erase(const K &key) {
    if (auto p = find(key); !p) return false;
    else if (tag_t::count(p) == 1) return erase(p), true;
    else return tag_t::modify_size(p, -1), true;
  }
  CEXP const_pointer erase(pointer p) {
    if (!p) return nullptr;
    pointer result;
    if (p->ch[0] && p->ch[1]) {
      auto s = tag_t::leftmost(p->ch[1]);
      std::swap(s->data, p->data),
        tag_t::modify_size(s, (i32)tag_t::count(p) - (i32)tag_t::count(s), p),
        result = p, p = s;
    } else result = tag_t::next(p);
    return tag_t::modify_size(p, -(i32)tag_t::count(p)),
           tag_t::erase_branch_leaf(root, p), alloc.deallocate(p, 1), result;
  }

private:
  Alloc<node_t> alloc;
};
}  // namespace tifa_libs::ds
namespace tifa_libs::ds {
struct rbt_tag: bst_tag {
  template <class pointer>
  static CEXP bool is_red(pointer p) {
    return p ? p->red : false;
  }
  template <class pointer>
  static CEXP void insert_leaf(pointer &root, pointer p, pointer n, bool dir) {
    n->red = p, bst_tag::insert_leaf(root, p, n, dir);
    while (is_red(p = n->fa)) {
      bool p_dir = p->child_dir();
      auto g = p->fa, u = g->ch[!p_dir];
      if (is_red(u)) {
        p->red = u->red = false, g->red = true, n = g;
        continue;
      }
      if (n->child_dir() != p_dir) rotate(root, p, p_dir), swap(n, p);
      p->red = false, g->red = true, rotate(root, g, !p_dir);
    }
    root->red = false;
  }
  template <class pointer>
  static CEXP void erase_branch_leaf(pointer &root, pointer n) {
    bool n_dir = n == root ? false : n->child_dir();
    bst_tag::erase_branch_leaf(root, n);
    auto p = n->fa;
    if (!p) {
      if (root) root->red = false;
      return;
    } else if (auto s = p->ch[n_dir]; s) return void(s->red = false);
    while (p && !n->red) {
      auto s = p->ch[!n_dir];
      if (is_red(s))
        s->red = false, p->red = true, rotate(root, p, n_dir),
        s = p->ch[!n_dir];
      auto c = s->ch[n_dir], d = s->ch[!n_dir];
      if (!is_red(c) && !is_red(d)) {
        if (s->red = true, n = p, p = n->fa; !p) break;
        n_dir = n->child_dir();
        continue;
      }
      if (!is_red(d))
        c->red = false, s->red = true, rotate(root, s, !n_dir),
        s = p->ch[!n_dir], c = s->ch[n_dir], d = s->ch[!n_dir];
      s->red = p->red, p->red = d->red = false, rotate(root, p, n_dir),
      n = root;
      break;
    }
    n->red = false;
  }
};
template <class K>
struct ostree_node_t<rbt_tag, K> {
  ostree_node_t *fa, *ch[2];
  K data;
  u32 sz;
  bool red;
  CEXP bool child_dir() const { return this == fa->ch[1]; }
};
template <class K, class Comp = std::less<K>>
using rbtree = ostree<K, rbt_tag, Comp>;
}  // namespace tifa_libs::ds
namespace tifa_libs {
CEXP u32 u32tostr_si16(u64 x, char *s) {
  if (x <= 9) return *s = (char)(x | 0x30), 1;
  else if (x <= 99) {
    u64 lo = x, ll = ((lo * 103) >> 9) & 0x1E;
    return lo += ll * 3, ll = ((lo & 0xF0) >> 4) | ((lo & 0x0F) << 8),
                         *(u16 *)s = (u16)(ll | 0x3030), 2;
  } else return 0;
}
CEXP u32 u32tostr_si32(u64 x, char *s) {
  u64 lo = 0, ll = 0;
  u32 digits = 0;
  if (x <= 99) return u32tostr_si16(x, s);
  lo = x, digits = (lo > 999) ? 4 : 3;
  ll = ((lo * 5243) >> 19) & 0xFF, lo = ((lo - ll * 100) << 16) | ll,
  ll = ((lo * 103) >> 9) & 0x1E001E, lo += ll * 3;
  ll =
    ((lo & 0x00F000F0) << 28) | ((lo & 0x000F000F) << 40) | 0x3030303000000000;
  if (u8 *p = (u8 *)&ll; digits == 4) *(u32 *)s = *(u32 *)(&p[4]);
  else *(u16 *)s = *(u16 *)(&p[5]), *(((u8 *)s) + 2) = p[7];
  return digits;
}
CEXP u32 u32tostr(u64 x, char *s) {
  u64 low = 0, ll = 0;
  u32 digits = 0;
  if (x <= 9999) return u32tostr_si32(x, s);
  if (x < 100000000) {
    if ((low = x) > 999999) digits = (low > 9999999) ? 8 : 7;
    else digits = (low > 99999) ? 6 : 5;
  } else {
    u64 high = (x * 0x55E63B89) >> 57;
    low = x - (high * 100000000), digits = u32tostr_si16(high, s) + 8;
  }
  ll = (low * 109951163) >> 40, (low -= ll * 10000) |= ll << 32;
  ll = ((low * 5243) >> 19) & 0x000000FF000000FF,
  low = ((low - ll * 100) << 16) | ll;
  ll = ((low * 103) >> 9) & 0x001E001E001E001E, low += ll * 3;
  ll = ((low & 0x00F000F000F000F0) >> 4) | (low & 0x000F000F000F000F) << 8;
  ll = (ll >> 32) | (ll << 32) | 0x3030303030303030;
  if (digits >= 8) memcpy(s + digits - 8, &ll, 8);
  else {
    u32 d = digits;
    char *s1 = s, *pll = &(((char *)&ll)[8 - digits]);
    if (d >= 4) memcpy(s1, pll, 4), s1 += 4, pll += 4, d -= 4;
    if (d >= 2) memcpy(s1, pll, 2), s1 += 2, pll += 2, d -= 2;
    if (d > 0) *(u8 *)s1 = *(u8 *)pll;
  }
  return digits;
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
  iterable_c<T> && !std::same_as<std::remove_cvref_t<T>, strn> &&
  !std::same_as<std::remove_cvref_t<T>, strnv>;
template <class, template <class...> class>
CEXP bool specialized_from_v = false;
template <template <class...> class T, class... Args>
CEXP bool specialized_from_v<T<Args...>, T> = true;
static_assert(specialized_from_v<vecu, std::vector>);
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
CEXP bool is_arithm_v = std::is_arithmetic_v<T> || is_int_v<T>;
template <class T>
concept arithm_c = is_arithm_v<T>;
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
concept adjlist_c = requires(T g) {
  g[0].begin();
  g[0].end();
  g.build();
  g.size();
  g.cnt_arc;
  g.deg_in;
  g.deg_out;
};
template <class T> concept adjlistw_c = adjlist_c<T> && !std::is_void_v<TPN T::w_t> && (requires(T g) { g[0].begin()->first; g[0].begin()->second; } || requires(T g) { g[0].begin()->to; g[0].begin()->cost; });
template <class T>
concept tree_c = adjlist_c<T> && requires(T g) { g.root; };
template <class T>
concept treew_c = adjlistw_c<T> && requires(T g) { g.root; };
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
using namespace std;
void solve(array<string_view, 2> boolmsg, bool multicase, auto &&func) {
  using R = decltype(func(int()));
  int t = 1;
  if (multicase) cin >> t;
  for (int i = 1; i <= t; i++) {
    if constexpr (same_as<R, void>) func(i);
    else if constexpr (same_as<R, bool>) cout << boolmsg[!func(i)] << '\n';
    else cout << func(i) << '\n';
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solve({"Yes", "No"}, true, [&]([[maybe_unused]] const int kase) {
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for (auto &[x, y] : a) cin >> x >> y;
    auto vt = std::ranges::to<std::vector>(a | views::keys);
    ranges::sort(vt);
    vt.erase(unique(vt.begin(), vt.end()), vt.end());
    vector vx = {INT_MIN};
    for (size_t i = 0; i < vt.size(); i++) {
      vx.push_back(vt[i]);
      if (i + 1 < vt.size() && vt[i + 1] - vt[i] > 1) vx.push_back(vt[i] + 1);
    }
    vx.push_back(INT_MAX);
    std::map<int, vector<int>> x2y;
    for (auto [x, y] : a) x2y[x].push_back(y);
    tifa_libs::ds::rbtree<int> above, below;
    for (auto [x, y] : a) below.insert(y);
    int ans = 0, ansx = 0, ansy = 0;
    for (auto x : vx) {
      int y = 0;
      auto check = [&](auto g) {
        if (!g) return true;
        auto f = [&](auto it) {
          if (!it) return false;
          int yy = it->data;
          int cnt1 = above.order_of_key(yy);
          int cnt2 = above.size() - cnt1;
          int cnt3 = below.order_of_key(yy);
          int cnt4 = below.size() - cnt3;
          if (min({cnt1, cnt2, cnt3, cnt4}) >= g) {
            y = yy;
            return true;
          }
          return false;
        };
        if (f(above.find_by_order(g))) return true;
        if (f(above.find_by_order(above.size() - g))) return true;
        if (f(below.find_by_order(g))) return true;
        if (f(below.find_by_order(below.size() - g))) return true;
        return false;
      };
      auto res = *ranges::partition_point(views::iota(0, n / 4 + 1), check);
      if (res - 1 > ans) {
        ans = res - 1;
        ansx = x;
        ansy = y;
      }
      for (auto y : x2y[x]) {
        above.insert(y);
        below.erase(y);
      }
    }
    cout << ans << '\n';
    cout << ansx << ' ' << ansy << '\n';
  });
  return 0;
}
