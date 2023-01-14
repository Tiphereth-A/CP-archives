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
using i64 = int64_t;
#define run_exec_(expressions, post_process) \
  {                                          \
    expressions;                             \
    post_process;                            \
  }
#define run_return_void_(expressions) run_exec_(expressions, return)
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
using namespace std;
auto solve([[maybe_unused]] int t_ = 0) -> void {
  i64 m, k, a1, ak;
  cin >> m >> k >> a1 >> ak;
  if (a1 > k) {
    ak += a1 / k - 1;
    a1 -= (a1 / k - 1) * k;
  }
  if (i64 _ = m / k; _ > ak) {
    m -= ak * k;
    ak = 0;
  } else {
    ak -= max(i64(0), _ - 1);
    m -= max(i64(0), _ - 1) * k;
  }
  i64 ans = max(i64(0), m / k - 1);
  m -= ans * k;
  if (m <= a1) run_return_void_(cout << ans << '\n');
  if (m < k) run_return_void_(cout << ans + m - a1 << '\n');
  if (m - k <= a1) run_return_void_(cout << ans + (ak ? 0 : 1) << '\n');
  run_return_void_(cout << ans + (ak ? 0 : 1) + (m - k - a1) << '\n');
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  int t_ = 0;
  std::cin >> t_;
  for (i_ = 0; i_ < t_; ++i_) solve(i_);
  return 0;
}
