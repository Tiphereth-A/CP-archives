#include <bits/stdc++.h>
#include <bits/stdtr1c++.h>
#include <ext/algorithm>
#include <ext/rb_tree>
#include <ext/rope>
#include <ext/vstring.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/exception.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/list_update_policy.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>
template <typename T>
using remove_cvref_t =
  typename std::remove_cv_t<typename std::remove_reference_t<T>>;
template <class T>
using is_iterable = typename std::conditional_t<
  std::is_same_v<decltype(std::declval<remove_cvref_t<T>>().begin()),
                 typename remove_cvref_t<T>::iterator> &&
    std::is_same_v<decltype(std::declval<remove_cvref_t<T>>().end()),
                   typename remove_cvref_t<T>::iterator>,
  std::true_type,
  std::false_type>;
template <class T>
using is_container = typename std::conditional_t<
  is_iterable<T>::value &&
    !std::is_base_of_v<T, std::basic_string<typename T::value_type>>,
  std::true_type,
  std::false_type>;
template <class T>
using vc = std::vector<T>;
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using i128 = __int128_t;
using u128 = __uint128_t;
#define for_(i, l, r, vars...)                                            \
  for (std::make_signed_t<decltype(l + r)> i = (l), i##end = (r), ##vars; \
       i <= i##end;                                                       \
       ++i)
template <class T>
constexpr auto chkmin(T &a, T b) -> bool {
  return b < a ? a = b, true : false;
}
template <class T>
constexpr auto chkmax(T &a, T b) -> bool {
  return a < b ? a = b, true : false;
}
template <class T>
constexpr auto ispow2(T i) -> bool {
  return i && (i & -i) == i;
}
template <class T, std::enable_if_t<is_container<T>::value> * = nullptr>
std::ostream &operator<<(std::ostream &os, const T &x) {
  if (x.begin() == x.end()) return os;
  for (auto it = x.begin(); it != x.end() - 1; ++it) os << *it << ' ';
  os << x.back();
  return os;
}
#define(std::cerr << __LINE__ << ' ' << __FUNCTION__ << std::endl)
constexpr i64 MOD = 998244353;
using namespace std;
namespace tifa_libs {
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using i128 = __int128_t;
using u128 = __uint128_t;
}  // namespace tifa_libs
namespace tifa_libs::bit {
template <typename T>
constexpr int cntl0(T x) {
  constexpr int nd = sizeof(T) * 8;
  if (x == 0) return nd;
  constexpr int nd_ull = sizeof(unsigned long long) * 8;
  constexpr int nd_ul = sizeof(unsigned long) * 8;
  constexpr int nd_u = sizeof(unsigned) * 8;
  if constexpr (nd <= nd_u) return __builtin_clz(x) - (nd_u - nd);
  else if constexpr (nd <= nd_ul) return __builtin_clzl(x) - (nd_ul - nd);
  else if constexpr (nd <= nd_ull) return __builtin_clzll(x) - (nd_ull - nd);
  else {
    static_assert(nd <= (2 * nd_ull),
                  "Maximum supported integer size is 128-bit");
    unsigned long long hi = x >> nd_ull;
    if (hi != 0) return __builtin_clzll(hi) - ((2 * nd_ull) - nd);
    unsigned long long lo = x & (unsigned long long)(-1);
    return (nd - nd_ull) + __builtin_clzll(lo);
  }
}
}  // namespace tifa_libs::bit
namespace tifa_libs::bit {
template <typename T>
constexpr int bwidth(T x) {
  return (int)sizeof(T) * 8 - cntl0(x);
}
}  // namespace tifa_libs::bit
namespace tifa_libs::math {
constexpr u32 isqrt(u64 x) {
  int c = (bit::bwidth(x) - 1) / 2, sh = 31 - c;
  u32 u = [](u64 x) {
    constexpr uint8_t TAB[192] = {
      128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142,
      143, 144, 144, 145, 146, 147, 148, 149, 150, 151, 151, 152, 153, 154, 155,
      156, 156, 157, 158, 159, 160, 160, 161, 162, 163, 164, 164, 165, 166, 167,
      167, 168, 169, 170, 170, 171, 172, 173, 173, 174, 175, 176, 176, 177, 178,
      179, 179, 180, 181, 181, 182, 183, 183, 184, 185, 186, 186, 187, 188, 188,
      189, 190, 190, 191, 192, 192, 193, 194, 194, 195, 196, 196, 197, 198, 198,
      199, 200, 200, 201, 201, 202, 203, 203, 204, 205, 205, 206, 206, 207, 208,
      208, 209, 210, 210, 211, 211, 212, 213, 213, 214, 214, 215, 216, 216, 217,
      217, 218, 219, 219, 220, 220, 221, 221, 222, 223, 223, 224, 224, 225, 225,
      226, 227, 227, 228, 228, 229, 229, 230, 230, 231, 232, 232, 233, 233, 234,
      234, 235, 235, 236, 237, 237, 238, 238, 239, 239, 240, 240, 241, 241, 242,
      242, 243, 243, 244, 244, 245, 246, 246, 247, 247, 248, 248, 249, 249, 250,
      250, 251, 251, 252, 252, 253, 253, 254, 254, 255, 255, 255};
    u32 u = TAB[(x >> 56) - 64];
    u = (u << 7) + (u32)(x >> 41) / u;
    return (u << 15) + (u32)((x >> 17) / u);
  }(x << 2 * sh);
  u >>= sh;
  u -= (u64)u * u > x;
  return u;
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class F1, class F2, class F3>
inline std::vector<u32>
linear_seive(u32 n, F1 cb_prime, F2 cb_coprime, F3 cb_not_coprime) {
  std::vector<bool> vis(n);
  std::vector<u32> p;
  p.reserve(n <= 55 ? 16 : n / 10);
  for (u32 i = 2; i < n; ++i) {
    if (!vis[i]) {
      p.push_back(i);
      cb_prime(i);
    }
    for (u32 j : p) {
      if ((u64)i * j >= n) break;
      vis[i * j] = true;
      if (i % j) cb_coprime(i, j);
      else {
        cb_not_coprime(i, j);
        break;
      }
    }
  }
  return p;
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
class Rgcd {
  struct F3 {
    u32 a, b, c;
    F3(u32 _a = 0, u32 _b = 0, u32 _c = 0): a(_a), b(_b), c(_c) {}
  };
  std::vector<F3> fs;
  std::vector<std::vector<u32>> g_;

public:
  explicit Rgcd(u32 n)
    : fs(n), g_(isqrt(n) + 1, decltype(g_)::value_type(isqrt(n) + 1)) {
    fs[1] = {1, 1, 1};
    linear_seive(
      n,
      [this](u32 p) { fs[p] = {1, 1, p}; },
      [this](u32 i, u32 j) {
        F3 &now = fs[i * j];
        now = fs[i];
        if ((now.a *= j) > now.b) std::swap(now.a, now.b);
        if (now.b > now.c) std::swap(now.b, now.c);
      },
      [this]([[maybe_unused]] u32 i, [[maybe_unused]] u32 j) {
        F3 &now = fs[i * j];
        now = fs[i];
        if ((now.a *= j) > now.b) std::swap(now.a, now.b);
        if (now.b > now.c) std::swap(now.b, now.c);
      });
    for (size_t i = 1; i < g_.size(); ++i) {
      g_[i][0] = g_[0][i] = g_[i][i] = (u32)i;
      for (size_t j = 1; j < i; ++j) g_[i][j] = g_[j][i] = g_[j][i % j];
    }
  }
  u32 operator()(u32 x, u32 y) const {
    assert(x < fs.size() && y < fs.size());
    if (x < g_.size() && y < g_.size()) return g_[x][y];
    u32 ans = 1, _;
    for (u32 i : {fs[x].a, fs[x].b, fs[x].c}) {
      y /= (_ = i < g_.size() ? g_[i][y % i] : (y % i == 0) * (i - 1) + 1);
      ans *= _;
    }
    return ans;
  }
};
}  // namespace tifa_libs::math
auto solve([[maybe_unused]] int t_ = 0) -> void {
  tifa_libs::math::Rgcd qgcd(1000'001);
  u64 n;
  cin >> n;
  vc<int> a(n + 1), b(n + 1);
  for_(i, 1, n) cin >> a[i];
  for_(i, 1, n) cin >> b[i];
  for_(i, 1, n) {
    u64 ans = 0, i_ = i;
    for_(j, 1, n) {
      ans += i_ * qgcd(a[i], b[j]) % MOD;
      i_ = i_ * i % MOD;
    }
    cout << ans % MOD << '\n';
  }
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  // std::cout << std::fixed << std::setprecision(12);
  solve(i_);
  return 0;
}
