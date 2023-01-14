#include <bits/stdc++.h>
using ll = long long;
using i64 = ll;
using pll = std::pair<ll, ll>;
template <class Tp>
using vc = std::vector<Tp>;
#define for_(i, l, r, v...) for (ll i = (l), i##e = (r), ##v; i <= i##e; ++i)
using namespace std;
template <class Tp = int>
class Chtholly {
public:
  struct Node {
    size_t l, r;
    mutable Tp v;
    Node(size_t const &l, size_t const &r, Tp const &v): l(l), r(r), v(v) {}
    bool operator<(Node const &o) const { return l < o.l; }
  };

protected:
  std::set<Node> data;
  size_t n;
  auto split(size_t x) {
    if (x >= n) return data.end();
    auto it = data.upper_bound(Node{x, 0, 0});
    if ((--it)->l == x) return it;
    auto [l, r, v] = *it;
    data.erase(it);
    data.emplace(l, x - 1, v);
    return data.emplace(x, r, v).first;
  }

public:
  explicit Chtholly(std::vector<Tp> const &c): data(), n(c.size()) {
    size_t cnt = 0;
    for (auto &&i : c) {
      data.emplace(cnt, cnt, i);
      ++cnt;
    }
  }
  void assign(size_t l, size_t r, Tp const &v) {
    auto itr = split(r + 1), itl = split(l);
    data.erase(itl, itr);
    data.emplace(l, r, v);
  }
  template <class Func>
  void run(size_t l, size_t r, Func func) {
    for (auto itr = split(r + 1), itl = split(l); itl != itr; ++itl) func(itl);
  }
};
constexpr int64_t qpow(int64_t a, int64_t b, int64_t mod) {
  int64_t res(1);
  a %= mod;
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
template <
  class Ch,
  class Tr,
  class Ct,
  std::enable_if_t<std::is_same<decltype(std::declval<Ct>().begin()),
                                typename Ct::iterator>::value &&
                   std::is_same<decltype(std::declval<Ct>().end()),
                                typename Ct::iterator>::value> * = nullptr>
std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os,
                                       const Ct &x) {
  if (x.begin() == x.end()) return os;
  for (auto it = x.begin(); it != x.end() - 1; ++it) os << *it << ' ';
  os << x.back();
  return os;
}
void solve(int t_ = 0) {
  i64 n, m, seed, vmax;
  cin >> n >> m >> seed >> vmax;
  auto rnd = [&]() {
    auto ret = seed;
    seed = (seed * 7 + 13) % 1000000007;
    return ret;
  };
  vc<i64> a(n);
  for (auto &i : a) i = rnd() % vmax + 1;
  Chtholly<i64> odt(a);
  for_(i, 1, m, op, l, r, x, y) {
    op = rnd() % 4 + 1;
    l = rnd() % n + 1;
    r = rnd() % n + 1;
    if (l > r) swap(l, r);
    if (op == 3) x = rnd() % (r - l + 1) + 1;
    else x = (rnd() % vmax) + 1;
    if (op == 4) y = (rnd() % vmax) + 1;
    --l;
    --r;
    i64 ans;
    vc<pll> v_;
    switch (op) {
      case 1: odt.run(l, r, [&](auto it) { it->v += x; }); break;
      case 2: odt.assign(l, r, x); break;
      case 3:
        odt.run(
          l, r, [&](auto it) { v_.emplace_back(it->v, it->r - it->l + 1); });
        sort(v_.begin(), v_.end());
        for (auto &&[k, cnt] : v_)
          if ((x -= cnt) <= 0) {
            cout << k << '\n';
            break;
          }
        break;
      case 4:
        ans = 0;
        odt.run(l, r, [&](auto it) {
          (ans += qpow(it->v, x, y) * (it->r - it->l + 1) % y) %= y;
        });
        cout << ans << '\n';
        break;
      default: exit(__LINE__);
    }
  }
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  solve(i_);
  return 0;
}
