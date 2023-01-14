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
  typename std::remove_cv<typename std::remove_reference<T>::type>::type;
template <class T>
using is_iterable = typename std::conditional<
  std::is_same<decltype(std::declval<remove_cvref_t<T>>().begin()),
               typename remove_cvref_t<T>::iterator>::value &&
    std::is_same<decltype(std::declval<remove_cvref_t<T>>().end()),
                 typename remove_cvref_t<T>::iterator>::value,
  std::true_type,
  std::false_type>::type;
template <class Tp>
using pi = std::pair<Tp, Tp>;
template <class Tp>
using vc = std::vector<Tp>;
using pii = pi<int>;
#define for_(i, l, r, vars...)                                            \
  for (std::make_signed_t<decltype(l + r)> i = (l), i##end = (r), ##vars; \
       i <= i##end;                                                       \
       ++i)
#define foreach_ref_(i, container) for (auto &i : container)
#define read_container_(type, name, size) \
  type name(size);                        \
  foreach_ref_(i, name) std::cin >> i
using namespace std;
namespace Enumerate {
template <typename T, std::enable_if_t<is_iterable<T>::value> * = nullptr>
class enumerate_impl_ {
public:
  using iter_t = typename remove_cvref_t<T>::iterator;

private:
  const T &container_;
  size_t sz_;
  iter_t now_;

public:
  enumerate_impl_(T x): container_(x), sz_(0), now_(x.begin()) {}
  const enumerate_impl_ &begin() const { return *this; }
  const enumerate_impl_ &end() const { return *this; }
  bool operator!=(const enumerate_impl_ &) const {
    return now_ != container_.end();
  }
  void operator++() {
    ++now_;
    ++sz_;
  }
  std::pair<std::size_t, iter_t> operator*() const { return {sz_, now_}; }
};
template <typename T>
enumerate_impl_<T> enumerate(T &&container) {
  return {std::forward<T>(container)};
}
}  // namespace Enumerate
using Enumerate::enumerate;
auto solve([[maybe_unused]] int t_ = 0) -> void {
  int n;
  cin >> n;
  read_container_(vc<int>, a, n * 2);
  vc<pii> b;
  b.reserve(n * 2);
  for (auto [idx, iter] : enumerate(a)) b.emplace_back(*iter, idx);
  partial_sort(b.begin(), b.begin() + n, b.end());
  vc<bool> lo(n * 2);
  for_(i, 0, n - 1) lo[b[i].second] = 1;
  char lo_ch = ')' ^ lo[0];
  string ans(n * 2, '*');
  vc<int> stk;
  stk.push_back(0);
  for_(i, 1, n * 2 - 1)
    if (stk.empty()) stk.push_back(i);
    else if (lo[stk.back()] ^ lo[i]) {
      ans[stk.back()] = '(';
      ans[i] = ')';
      stk.pop_back();
    } else stk.push_back(i);
  cout << ans << '\n';
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
