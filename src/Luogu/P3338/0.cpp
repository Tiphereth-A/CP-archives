#include <iomanip>
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
const double PI = acos(-1.);
using namespace std;
namespace FFT {
using CP = std::complex<double>;
const double PI = acos(-1.0);
size_t n = 0;
std::vector<size_t> rev;
void init(size_t m) {
  if (n > m) return;
  n = 1;
  int k = 0;
  while (n <= m) {
    n <<= 1;
    ++k;
  }
  rev.resize(n);
  for (int i = 0; i < n; ++i)
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
}
void dft(std::vector<CP> &a, int op) {
  for (int i = 0; i < n; ++i)
    if (rev[i] > i) std::swap(a[rev[i]], a[i]);
  for (int i = 1; i < n; i <<= 1) {
    CP now(std::cos(PI / i), op * std::sin(PI / i));
    for (int j = 0, p = (i << 1); j < n; j += p) {
      CP w(1, 0);
      for (int k = 0; k < i; ++k, w = w * now) {
        CP x = a[j + k], y = a[j + k + i] * w;
        a[j + k] = x + y;
        a[j + k + i] = x - y;
      }
    }
  }
  if (op == -1)
    for (int i = 0; i < n; ++i) a[i] = {a[i].real() / n, a[i].imag() / n};
}
std::vector<double> conv(std::vector<double> const &a,
                         std::vector<double> const &b) {
  init(a.size() + b.size() - 1);
  std::vector<CP> a_(n), b_(n), c_(n);
  for (size_t i = 0; i < a.size(); ++i) a_[i] = a[i];
  for (size_t i = 0; i < b.size(); ++i) b_[i] = b[i];
  dft(a_, 1);
  dft(b_, 1);
  for (size_t i = 0; i < n; ++i) c_[i] = a_[i] * b_[i];
  dft(c_, -1);
  std::vector<double> c(a.size() + b.size() - 1);
  for (size_t i = 0; i < a.size() + b.size() - 1; ++i) c[i] = c_[i].real();
  return c;
}
}  // namespace FFT
using FFT::conv;
auto solve([[maybe_unused]] int t_ = 0) -> void {
  int n;
  cin >> n;
  vc<double> a(n);
  for (auto &i : a) cin >> i;
  vc<double> b(n * 2 - 1);
  for_(i, -n + 1, -1) b[i + n - 1] = -1. / i / i;
  for_(i, 1, n - 1) b[i + n - 1] = 1. / i / i;
  a = conv(a, b);
  cout << fixed << setprecision(3);
  for_(i, 0, n - 1) cout << a[i + n - 1] << '\n';
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
