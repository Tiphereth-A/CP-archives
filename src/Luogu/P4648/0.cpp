#include <bits/stdc++.h>
using namespace std;
using u32 = std::uint32_t;
using i64 = std::int64_t;
#define OPERATOR_OVERRIED_PAIR_(oper)                                         \
  template <class Tp, class Up>                                               \
  constexpr std::pair<Tp, Up> &operator oper##=(                              \
    std::pair<Tp, Up> &lhs, const std::pair<Tp, Up> &rhs) {                   \
    lhs.first oper## = rhs.first;                                             \
    lhs.second oper## = rhs.second;                                           \
    return lhs;                                                               \
  }                                                                           \
  template <class Tp, class Up>                                               \
  constexpr std::pair<Tp, Up> operator oper(std::pair<Tp, Up> lhs,            \
                                            const std::pair<Tp, Up> &rhs) {   \
    return lhs oper## = rhs;                                                  \
  }                                                                           \
  template <class Tp, class Up, class Vp>                                     \
  constexpr std::tuple<Tp, Up, Vp> &operator oper##=(                         \
    std::tuple<Tp, Up, Vp> &lhs, const std::tuple<Tp, Up, Vp> &rhs) {         \
    std::get<0>(lhs) oper## = std::get<0>(rhs);                               \
    std::get<1>(lhs) oper## = std::get<1>(rhs);                               \
    std::get<2>(lhs) oper## = std::get<2>(rhs);                               \
    return lhs;                                                               \
  }                                                                           \
  template <class Tp, class Up, class Vp>                                     \
  constexpr std::tuple<Tp, Up, Vp> operator oper(                             \
    std::tuple<Tp, Up, Vp> lhs, const std::tuple<Tp, Up, Vp> &rhs) {          \
    return lhs oper## = rhs;                                                  \
  }                                                                           \
  template <class Tp, class Up, class Vp, class Wp>                           \
  constexpr std::tuple<Tp, Up, Vp, Wp> &operator oper##=(                     \
    std::tuple<Tp, Up, Vp, Wp> &lhs, const std::tuple<Tp, Up, Vp, Wp> &rhs) { \
    std::get<0>(lhs) oper## = std::get<0>(rhs);                               \
    std::get<1>(lhs) oper## = std::get<1>(rhs);                               \
    std::get<2>(lhs) oper## = std::get<2>(rhs);                               \
    std::get<3>(lhs) oper## = std::get<3>(rhs);                               \
    return lhs;                                                               \
  }                                                                           \
  template <class Tp, class Up, class Vp, class Wp>                           \
  constexpr std::tuple<Tp, Up, Vp, Wp> operator oper(                         \
    std::tuple<Tp, Up, Vp, Wp> lhs, const std::tuple<Tp, Up, Vp, Wp> &rhs) {  \
    return lhs oper## = rhs;                                                  \
  }
OPERATOR_OVERRIED_PAIR_(+)
OPERATOR_OVERRIED_PAIR_(-)
OPERATOR_OVERRIED_PAIR_(*)
OPERATOR_OVERRIED_PAIR_(/)
OPERATOR_OVERRIED_PAIR_(%)
#undef OPERATOR_OVERRIED_PAIR_
template <class Ch, class Tr, class Tp, class Up>
std::basic_istream<Ch, Tr> &operator>>(std::basic_istream<Ch, Tr> &is,
                                       std::pair<Tp, Up> &p) {
  return is >> p.first >> p.second;
}
template <class Ch, class Tr, class Tp, class Up>
std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os,
                                       const std::pair<Tp, Up> &p) {
  return os << p.first << ' ' << p.second;
}
template <class Ch, class Tr, class Tp, class Up, class Vp>
std::basic_istream<Ch, Tr> &operator>>(std::basic_istream<Ch, Tr> &is,
                                       std::tuple<Tp, Up, Vp> &p) {
  return is >> std::get<0>(p) >> std::get<1>(p) >> std::get<2>(p);
}
template <class Ch, class Tr, class Tp, class Up, class Vp>
std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os,
                                       const std::tuple<Tp, Up, Vp> &p) {
  return os << std::get<0>(p) << ' ' << std::get<1>(p) << ' ' << std::get<2>(p);
}
template <class Ch, class Tr, class Tp, class Up, class Vp, class Wp>
std::basic_istream<Ch, Tr> &operator>>(std::basic_istream<Ch, Tr> &is,
                                       std::tuple<Tp, Up, Vp, Wp> &p) {
  return is >> std::get<0>(p) >> std::get<1>(p) >> std::get<2>(p) >>
         std::get<3>(p);
}
template <class Ch, class Tr, class Tp, class Up, class Vp, class Wp>
std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os,
                                       const std::tuple<Tp, Up, Vp, Wp> &p) {
  return os << std::get<0>(p) << ' ' << std::get<1>(p) << ' ' << std::get<2>(p)
            << ' ' << std::get<3>(p);
}
template <class Tp>
using pi = std::pair<Tp, Tp>;
template <class Tp>
using pi4 = std::tuple<Tp, Tp, Tp, Tp>;
template <class Tp>
using vc = std::vector<Tp>;
using pii64 = pi<i64>;
using pi4i64 = pi4<i64>;
#define for_(i, l, r, vars...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vars; i <= i##end; ++i)
#define foreach_ref_(i, container) for (auto &i : (container))
#define all_(a) (a).begin(), (a).end()
#define read_container_(type, name, size) \
  type name(size);                        \
  foreach_ref_(i, name) std::cin >> i;
template <class Tp>
constexpr auto chkmin(Tp &a, Tp b) -> bool {
  return b < a ? a = b, true : false;
};
template <class Tp>
constexpr auto chkmax(Tp &a, Tp b) -> bool {
  return a < b ? a = b, true : false;
};
template <class Tp>
auto discretization(Tp &var) -> Tp {
  Tp d__(var);
  std::sort(d__.begin(), d__.end());
  d__.erase(std::unique(d__.begin(), d__.end()), d__.end());
  for (auto &i : var)
    i = std::distance(d__.begin(), std::lower_bound(d__.begin(), d__.end(), i));
  return d__;
};
template <class Tp>
constexpr auto ispow2(Tp i) -> bool {
  return i && (i & -i) == i;
}
template <class Ch, class Tr, class Container>
std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os,
                                       const Container &x) {
  if (&os == &std::cerr) os << "[";
  if (&os == &std::cerr)
    for (auto it = x.begin(); it != x.end() - 1; ++it) os << *it << ", ";
  else
    for (auto it = x.begin(); it != x.end() - 1; ++it) os << *it << ' ';
  os << x.back();
  if (&os == &std::cerr) os << "]";
  return os;
}
const u32 OFFSET = 5;
const u32 N = 5e5 + OFFSET;
namespace kase1 {
i64 main(i64 n, i64 d, [[maybe_unused]] i64 m) {
  read_container_(vc<i64>, vec, n);
  sort(all_(vec));
  i64 ans = 0;
  for_(i, 0, n - 1, j = 0) {
    while (j < i && vec[i] - vec[j] > d) ++j;
    ans += i - j;
  }
  return ans;
}
}  // namespace kase1
namespace kase2 {
template <size_t N, class Tp>
class BIT {
protected:
  Tp tree[N];
  constexpr ptrdiff_t lowbit(ptrdiff_t x) const { return x & (-x); }

public:
  BIT() = default;
  void clear() { memset(tree, 0, sizeof(tree)); }
  void modify(size_t pos, Tp val = 1) {
    for (ptrdiff_t i = pos; i < N; i += lowbit(i)) tree[i] += val;
  }
  Tp query(ptrdiff_t pos) const {
    Tp ret = 0;
    for (ptrdiff_t i = clamp(pos, ptrdiff_t(0), ptrdiff_t(N) - 1); i;
         i -= lowbit(i))
      ret += tree[i];
    return ret;
  }
};
BIT<150'005, i64> tr;
i64 main(i64 n, i64 d, i64 m) {
  tr.clear();
  vc<pii64> vec;
  vec.reserve(n);
  for_(i, 1, n, x, y) {
    cin >> x >> y;
    vec.emplace_back(x + y, x - y);
  }
  sort(all_(vec));
  i64 ans = 0;
  for_(i, 0, n - 1, j = 0) {
    while (j < i && vec[i].first - vec[j].first > d)
      tr.modify(vec[j++].second + m, -1);
    ans +=
      tr.query(vec[i].second + d + m) - tr.query(vec[i].second - d - 1 + m);
    tr.modify(vec[i].second + m);
  }
  return ans;
}
}  // namespace kase2
namespace kase3 {
template <size_t N, class Tp>
class BIT3 {
protected:
  Tp tree[N][N][N];
  constexpr ptrdiff_t lowbit(ptrdiff_t x) const { return x & (-x); }

public:
  BIT3() = default;
  void clear() { memset(tree, 0, sizeof(tree)); }
  void modify(size_t x, size_t y, size_t z, Tp val = 1) {
    for (ptrdiff_t i = x; i < N; i += lowbit(i))
      for (ptrdiff_t j = y; j < N; j += lowbit(j))
        for (ptrdiff_t k = z; k < N; k += lowbit(k)) tree[i][j][k] += val;
  }
  Tp query(ptrdiff_t x, ptrdiff_t y, ptrdiff_t z) const {
    Tp ret = 0;
    for (ptrdiff_t i = clamp(x, ptrdiff_t(0), ptrdiff_t(N) - 1); i;
         i -= lowbit(i))
      for (ptrdiff_t j = clamp(y, ptrdiff_t(0), ptrdiff_t(N) - 1); j;
           j -= lowbit(j))
        for (ptrdiff_t k = clamp(z, ptrdiff_t(0), ptrdiff_t(N) - 1); k;
             k -= lowbit(k))
          ret += tree[i][j][k];
    return ret;
  }
};
BIT3<259, i64> tr;
i64 query(i64 l1, i64 r1, i64 l2, i64 r2, i64 l3, i64 r3) {
  return tr.query(r1, r2, r3) - tr.query(l1, r2, r3) - tr.query(r1, l2, r3) -
         tr.query(r1, r2, l3) + tr.query(l1, l2, r3) + tr.query(l1, r2, l3) +
         tr.query(r1, l2, l3) - tr.query(l1, l2, l3);
}
i64 main(i64 n, i64 d, i64 m) {
  tr.clear();
  vc<pi4i64> vec;
  vec.reserve(n);
  for_(i, 1, n, x, y, z) {
    cin >> x >> y >> z;
    vec.emplace_back(x + y + z, x + y - z, x - y + z, -x + y + z);
  }
  sort(all_(vec));
  i64 ans = 0;
  for_(i, 0, n - 1, j = 0) {
    while (j < i && get<0>(vec[i]) - get<0>(vec[j]) > d) {
      tr.modify(get<1>(vec[j]) + m, get<2>(vec[j]) + m, get<3>(vec[j]) + m, -1);
      ++j;
    }
    ans += query(get<1>(vec[i]) - d - 1 + m,
                 get<1>(vec[i]) + d + m,
                 get<2>(vec[i]) - d - 1 + m,
                 get<2>(vec[i]) + d + m,
                 get<3>(vec[i]) - d - 1 + m,
                 get<3>(vec[i]) + d + m);
    tr.modify(get<1>(vec[i]) + m, get<2>(vec[i]) + m, get<3>(vec[i]) + m);
  }
  return ans;
}
}  // namespace kase3
i64 (* const func[3])(i64, i64, i64) = {kase1::main, kase2::main, kase3::main};
auto solve([[maybe_unused]] int t_) -> void {
  i64 b, n, d, m;
  cin >> b >> n >> d >> m;
  cout << func[b - 1](n, d, m);
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
