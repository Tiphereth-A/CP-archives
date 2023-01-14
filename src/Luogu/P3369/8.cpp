#include <bits/extc++.h>
#define CEXP constexpr
#define CEXPE constexpr explicit
#define CR const &
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
  CEXP w operator""_##w(unsigned long long x) { return (w)x; }
mk_(i8, int8_t) mk_(u8, uint8_t) mk_(i16, int16_t) mk_(u16, uint16_t)
  mk_(i32, int32_t) mk_(u32, uint32_t) mk_(i64, int64_t) mk_(u64, uint64_t)
    mk_(isz, ptrdiff_t) mk_(usz, size_t);
#undef mk_
using u128 = __uint128_t;
using f128 = long double;
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
namespace tifa_libs::rand {
template <class T>
requires std::is_arithmetic_v<T>
class Gen {
  using res_t = std::conditional_t<sizeof(T) <= 4, u32, u64>;
  using res_wt = std::conditional_t<sizeof(T) <= 4, u64, u128>;
  struct mt19937_param {
    static CEXP u32 w = 32, n = 624, m = 397, r = 31, a = 0x9908b0df, u = 11,
                    d = 0xffffffff, s = 7, b = 0x9d2c5680, t = 15,
                    c = 0xefc60000, l = 18, f = 1812433253;
  };
  struct mt19937_64_param {
    static CEXP u64 w = 64, n = 312, m = 156, r = 31, a = 0xb5026f5aa96619e9,
                    u = 29, d = 0x5555555555555555, s = 17,
                    b = 0x71d67fffeda60000, t = 37, c = 0xfff7eee000000000,
                    l = 43, f = 6364136223846793005;
  };
  using pm = std::
    conditional_t<std::is_same_v<res_t, u32>, mt19937_param, mt19937_64_param>;
  T a_, b_;
  res_t x_[pm::n];
  u32 p_;
  CEXP void gen() {
    CEXP res_t um = (~res_t()) << pm::r, lm = ~um;
    res_t _;
    flt_(res_t, i, p_ = 0, pm::n - pm::m)
      _ = ((x_[i] & um) | (x_[i + 1] & lm)),
      x_[i] = (x_[i + pm::m] ^ (_ >> 1) ^ ((_ & 1) ? pm::a : 0));
    flt_(res_t, i, pm::n - pm::m, pm::n - 1)
      _ = ((x_[i] & um) | (x_[i + 1] & lm)),
      x_[i] = (x_[i + (pm::m - pm::n)] ^ (_ >> 1) ^ ((_ & 1) ? pm::a : 0));
    _ = ((x_[pm::n - 1] & um) | (x_[0] & lm)),
    x_[pm::n - 1] = (x_[pm::m - 1] ^ (_ >> 1) ^ ((_ & 1) ? pm::a : 0));
  }

public:
  CEXPE Gen(T a = std::numeric_limits<T>::min(),
            T b = std::numeric_limits<T>::max(),
            res_t sd = (res_t)TIME)
    : a_(a), b_(b) {
    assert(a < b || (std::is_integral_v<T> && a == b)), seed(sd);
  }
  CEXP void range(T min, T max) {
    assert(min < max || (std::is_integral_v<T> && min == max)), a_ = min,
                                                                b_ = max;
  }
  void seed() {
    seed((res_t)std::chrono::duration_cast<std::chrono::nanoseconds>(
           std::chrono::high_resolution_clock::now().time_since_epoch())
           .count());
  }
  CEXP void seed(res_t sd) {
    x_[0] = sd & gen_max();
    flt_(res_t, i, 1, p_ = pm::n) x_[i] =
      ((x_[i - 1] ^ (x_[i - 1] >> (pm::w - 2))) * pm::f + i % pm::n) &
      gen_max();
  }
  CEXP res_t gen_min() const { return 0; }
  CEXP res_t gen_max() const {
    return sizeof(res_t) * 8 == pm::w ? ~res_t() : ((res_t)1 << pm::w) - 1;
  }
  CEXP res_t next() {
    if (p_ >= pm::n) gen();
    res_t _ = x_[p_++];
    return _ ^= (_ >> pm::u) & pm::d, _ ^= (_ << pm::s) & pm::b,
           _ ^= (_ << pm::t) & pm::c, _ ^= (_ >> pm::l), _;
  }
  CEXP T operator()() {
    if CEXP (std::integral<T>) {
      res_wt r = (res_wt)b_ - (res_wt)a_ + 1, p = r * next();
      if (res_t l = (res_t)p, _ = res_t(res_wt(-(res_t)r) % r); l < r)
        while (l < _) l = res_t(p = r * next());
      return (T)(p >> pm::w) + a_;
    } else return T(next() / (f128)((u128)gen_max() + 1) * (b_ - a_) + a_);
  }
};
}  // namespace tifa_libs::rand
namespace tifa_libs::ds {
template <class T, bool recovery = false, class Comp = std::less<T>>
class fhq_treap {
  static constexpr Comp compare{};
  struct TIFA {
    T val;
    u32 r, sz, son[2];
  };
  rand::Gen<u32> rnd;
  vec<TIFA> tree;
  vecu stk;
  u32 root;
  u32 new_node(cT_(T) val) {
    u32 ret;
    if CEXP (recovery && stk.size())
      tree[ret = stk.back()] = {val, rnd(), 1, {0, 0}}, stk.pop_back();
    else ret = (u32)tree.size(), tree.push_back(TIFA{val, rnd(), 1, {0, 0}});
    return ret;
  }
  void pushup(u32 pos) {
    tree[pos].sz = tree[tree[pos].son[0]].sz + 1 + tree[tree[pos].son[1]].sz;
  }
  template <bool strict = false>
  pttu split_root(u32 pos, cT_(T) key) {
    if (!pos) return {};
    bool f;
    if CEXP (strict) f = compare(tree[pos].val, key);
    else f = !compare(key, tree[pos].val);
    if (f) {
      auto [l, r] = split_root<strict>(tree[pos].son[1], key);
      tree[pos].son[1] = l;
      pushup(pos);
      return {pos, r};
    }
    auto [l, r] = split_root<strict>(tree[pos].son[0], key);
    tree[pos].son[0] = r;
    pushup(pos);
    return {l, pos};
  }
  u32 merge_root(u32 l, u32 r) {
    if (!l | !r) return l | r;
    if (tree[l].r < tree[r].r) {
      tree[l].son[1] = merge_root(tree[l].son[1], r), pushup(l);
      return l;
    }
    tree[r].son[0] = merge_root(l, tree[r].son[0]), pushup(r);
    return r;
  }

public:
  CEXPE fhq_treap(u32 seed = TIME)
    : rnd(0, -1_u32, seed), tree{1}, stk{}, root{} {
    tree[0].sz = {};
  }
  void insert(cT_(T) val) {
    u32 tar = new_node(val);
    auto dfs = [&](auto &&f, u32 &pos) -> void {
      if (!pos) return void(pos = tar);
      if (tree[tar].r < tree[pos].r) {
        auto [l, r] = split_root<true>(pos, val);
        tree[tar].son[0] = l;
        tree[tar].son[1] = r;
        pos = tar;
      } else
        f(f, compare(tree[pos].val, val) ? tree[pos].son[1] : tree[pos].son[0]);
      pushup(pos);
    };
    dfs(dfs, root);
  }
  bool erase(cT_(T) val) {
    auto dfs = [&](auto &&f, u32 &pos) -> bool {
      if (!pos) return false;
      if (tree[pos].val == val) {
        if CEXP (recovery) stk.push_back(pos);
        return pos = merge_root(tree[pos].son[0], tree[pos].son[1]), true;
      }
      if (!f(f,
             compare(tree[pos].val, val) ? tree[pos].son[1] : tree[pos].son[0]))
        return false;
      return pushup(pos), true;
    };
    return dfs(dfs, root);
  }
  auto find(cT_(T) val) const {
    u32 pos = root;
    while (pos) {
      if (val == tree[pos].val) return tree.cbegin() + pos;
      else pos = tree[pos].son[!compare(val, tree[pos].val)];
    }
    return tree.cend();
  }
  u32 rank(cT_(T) val) const {
    u32 pos = root, res = 0;
    while (pos) {
      if (compare(tree[pos].val, val))
        res += tree[tree[pos].son[0]].sz + 1, pos = tree[pos].son[1];
      else pos = tree[pos].son[0];
    }
    return res + 1;
  }
  u32 count(cT_(T) val) const {
    u32 rk = rank(val);
    if (auto res = next(val); !res) return tree[root].sz - rk + 1;
    else return rank(res.value()) - rk;
  }
  std::optional<T> kth(u32 k) const {
    if (k < 1 || k > tree[root].sz) return {};
    u32 pos = root;
    while (true) {
      if (auto _ = tree[pos].sz - tree[tree[pos].son[1]].sz; _ == k)
        return tree[pos].val;
      else if (_ < k) k -= _, pos = tree[pos].son[1];
      else pos = tree[pos].son[0];
    }
  }
  std::optional<T> prev(cT_(T) val) const {
    u32 pos = root;
    std::pair<bool, T> res{false, {}};
    while (pos) {
      if (val <= tree[pos].val) {
        pos = tree[pos].son[0];
      } else {
        res = {true, tree[pos].val};
        pos = tree[pos].son[1];
      }
    }
    return res.second;
  }
  std::optional<T> next(cT_(T) val) const {
    u32 pos = root;
    std::pair<bool, T> res{false, {}};
    while (pos) {
      if (tree[pos].val <= val) {
        pos = tree[pos].son[1];
      } else {
        res = {true, tree[pos].val};
        pos = tree[pos].son[0];
      }
    }
    return res.second;
  }
};
}  // namespace tifa_libs::ds
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  tifa_libs::ds::fhq_treap<i32> treap;
  for (u32 i = 0, opt; i < n; ++i) {
    i32 x;
    std::cin >> opt >> x;
    if (opt == 1) treap.insert(x);
    else if (opt == 2) treap.erase(x);
    else if (opt == 3) std::cout << treap.rank(x) << '\n';
    else if (opt == 4) std::cout << treap.kth((u32)x).value() << '\n';
    else if (opt == 5) std::cout << treap.prev(x).value() << '\n';
    else std::cout << treap.next(x).value() << '\n';
  }
}
