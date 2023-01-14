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
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
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
class Qgcd {
  struct F3 {
    u32 a, b, c;
    F3(u32 _a = 0, u32 _b = 0, u32 _c = 0): a(_a), b(_b), c(_c) {}
  };
  std::vector<F3> factors;
  std::vector<std::vector<u32>> gcd_;

public:
  Qgcd(u32 n)
    : factors(n),
      gcd_((u32)sqrt(n) + 1, decltype(gcd_)::value_type((u32)sqrt(n) + 1)) {
    std::vector<bool> vis(n);
    std::vector<u32> prime;
    prime.reserve(n / 10);
    factors[1] = {1, 1, 1};
    for (u32 i = 2; i < n; ++i) {
      if (!vis[i]) {
        prime.push_back(i);
        factors[i] = {1, 1, i};
      }
      for (u32 j : prime) {
        if (i * j >= n) break;
        vis[i * j] = 1;
        F3 &now = factors[i * j];
        now = factors[i];
        if ((now.a *= j) > now.b) std::swap(now.a, now.b);
        if (now.b > now.c) std::swap(now.b, now.c);
        if (i % j == 0) break;
      }
    }
    for (size_t i = 1; i < gcd_.size(); ++i) {
      gcd_[i][0] = gcd_[0][i] = gcd_[i][i] = (u32)i;
      for (size_t j = 1; j < i; ++j) gcd_[i][j] = gcd_[j][i] = gcd_[j][i % j];
    }
  }
  u32 operator()(u32 x, u32 y) const {
    assert(x < factors.size() && y < factors.size());
    if (x < gcd_.size() && y < gcd_.size()) return gcd_[x][y];
    u32 ans = 1, _;
    for (u32 i : {factors[x].a, factors[x].b, factors[x].c}) {
      y /= (_ = i < gcd_.size() ? gcd_[i][y % i] : (y % i == 0) * (i - 1) + 1);
      ans *= _;
    }
    return ans;
  }
};
auto solve([[maybe_unused]] int t_ = 0) -> void {
  Qgcd qgcd(1000'001);
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
