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
template <class T>
using is_container = typename std::conditional<
  is_iterable<T>::value &&
    !std::is_base_of<T, std::basic_string<typename T::value_type>>::value,
  std::true_type,
  std::false_type>::type;
using i64 = int64_t;
#define for_(i, l, r, vars...)                                            \
  for (std::make_signed_t<decltype(l + r)> i = (l), i##end = (r), ##vars; \
       i <= i##end;                                                       \
       ++i)
#define run_exec_(expressions, post_process) \
  {                                          \
    expressions;                             \
    post_process;                            \
  }
#define run_return_void_(expressions) run_exec_(expressions, return)
template <class Tp>
constexpr auto chkmin(Tp &a, Tp b) -> bool {
  return b < a ? a = b, true : false;
}
template <class Tp>
constexpr auto chkmax(Tp &a, Tp b) -> bool {
  return a < b ? a = b, true : false;
}
template <class Tp>
constexpr auto ispow2(Tp i) -> bool {
  return i && (i & -i) == i;
}
#define OO_PTEQ_(op)                                                          \
  template <class Tp, class Up>                                               \
  constexpr auto operator op(std::pair<Tp, Up> lhs,                           \
                             const std::pair<Tp, Up> &rhs) {                  \
    return std::pair<Tp, Up>{lhs.first op rhs.first,                          \
                             lhs.second op rhs.second};                       \
  }                                                                           \
  template <class Tp, class Up>                                               \
  constexpr std::pair<Tp, Up> &operator op##=(std::pair<Tp, Up> &lhs,         \
                                              const std::pair<Tp, Up> &rhs) { \
    lhs.first op## = rhs.first;                                               \
    lhs.second op## = rhs.second;                                             \
    return lhs;                                                               \
  }
OO_PTEQ_(+)
OO_PTEQ_(-)
OO_PTEQ_(*)
OO_PTEQ_(/)
OO_PTEQ_(%)
OO_PTEQ_(&)
OO_PTEQ_(|)
OO_PTEQ_(^)
OO_PTEQ_(<<)
OO_PTEQ_(>>)
#undef OO_PTEQ_
template <class Tp, class Up>
std::istream &operator>>(std::istream &is, std::pair<Tp, Up> &p) {
  return is >> p.first >> p.second;
}
template <class Tp, class Up>
std::ostream &operator<<(std::ostream &os, const std::pair<Tp, Up> &p) {
  return os << p.first << ' ' << p.second;
}
template <class T, std::enable_if_t<is_container<T>::value> * = nullptr>
std::ostream &operator<<(std::ostream &os, const T &x) {
  if (x.begin() == x.end()) return os;
  for (auto it = x.begin(); it != x.end() - 1; ++it) os << *it << ' ';
  os << x.back();
  return os;
}
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
template <typename Tp>
class BIT {
protected:
  std::vector<Tp> tree;
  constexpr ptrdiff_t lowbit(ptrdiff_t x) const { return x & (-x); }

public:
  explicit BIT(size_t sz): tree(sz) {}
  void reset(size_t sz) { tree.resize(sz, 0); }
  void modify(ptrdiff_t pos, Tp val = 1) {
    if (pos < 1) return;
    pos = std::clamp(pos, ptrdiff_t(1), ptrdiff_t(tree.size()) - 1);
    for (ptrdiff_t i = pos; i < ptrdiff_t(tree.size()); i += lowbit(i))
      tree[i] += val;
  }
  Tp query(ptrdiff_t pos) const {
    Tp ret = 0;
    if (pos < 1) return 0;
    pos = std::clamp(pos, ptrdiff_t(1), ptrdiff_t(tree.size()) - 1);
    for (ptrdiff_t i = pos; i; i = i - lowbit(i)) ret += tree[i];
    return ret;
  }
};
using namespace std;
auto solve([[maybe_unused]] int t_ = 0) -> void {
  string s;
  cin >> s;
  array<deque<int>, 26> idx;
  for_(i, 0, s.size() - 1) idx[s[i] - 'A'].push_back(i + 1);
  {
    int cnt = 0;
    for (auto &&i : idx) cnt += i.size() & 1;
    if (cnt > 1) run_return_void_(cout << "-1\n");
  }
  BIT<i64> tr(s.size() + 1);
  for_(i, 1, s.size()) tr.modify(i);
  i64 ans = 0;
  for_(i, 1, s.size() / 2) {
    i64 _ = 11451419;
    int now_idx = 0;
    for (auto [i, it] : enumerate(idx)) {
      if (it->size() < 2) continue;
      if (i64 l = tr.query(it->front() - 1),
          r = tr.query(s.size()) - tr.query(it->back());
          l + r < _) {
        _ = l + r;
        now_idx = i;
      }
    }
    ans += _;
    tr.modify(idx[now_idx].front(), -1);
    tr.modify(idx[now_idx].back(), -1);
    idx[now_idx].pop_front();
    idx[now_idx].pop_back();
  }
  cout << ans << '\n';
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
