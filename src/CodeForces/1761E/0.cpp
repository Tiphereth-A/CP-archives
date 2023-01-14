#include <bits/stdc++.h>
using ll = long long;
template <class Tp>
using vc = std::vector<Tp>;
template <class Tp>
using vvc = std::vector<std::vector<Tp>>;
#define for_(i, l, r, v...) for (ll i = (l), i##e = (r), ##v; i <= i##e; ++i)
#define forit_(it, cont) \
  for (auto it = (cont).begin(); it != (cont).end(); ++it)
template <class Tp>
Tp dec(Tp &i) {
  return --i;
}
template <class Tp>
Tp inc(Tp &i) {
  return ++i;
}
using namespace std;
class DsuBasic {
protected:
  std::vector<size_t> fa;

public:
  explicit DsuBasic(size_t size): fa(size) {
    std::iota(fa.begin(), fa.end(), 0);
  }
  size_t find(size_t x) { return x == fa[x] ? fa[x] : fa[x] = find(fa[x]); }
  bool merge(size_t x, size_t y) {
    size_t fx = find(x), fy = find(y);
    return fx == fy ? false : (fa[fx] = fy, true);
  }
};
void solve(int t_ = 0) {
  int n;
  cin >> n;
  vvc<int> g(n + 1);
  DsuBasic dsu(n + 1);
  for_(i, 1, n)
    for_(j, 1, n)
      if (char ch; (cin >> ch), j < i && ch & 1) {
        g[i].push_back(j);
        g[j].push_back(i);
        dsu.merge(i, j);
      }
  map<int, vc<int>> lst;
  for_(i, 1, n) lst[dsu.find(i)].push_back(i);
  auto is_alone = [&](auto i) {
    return g[i].size() == 1 && lst[dsu.find(i)].size() > 2;
  };
  auto is_dominate = [&](auto i) {
    return g[i].size() + 1 == lst[dsu.find(i)].size();
  };
  if (lst.size() == 1) {
    cout << "0\n";
    return;
  }
  for (auto &&[k, v] : lst)
    if (v.size() == 1) {
      cout << "1\n" << v[0] << '\n';
      return;
    }
  for_(i, 1, n)
    if (is_alone(i)) {
      cout << "1\n" << i << '\n';
      return;
    }
  {
    int del = 0;
    for_(i, 1, n)
      if (!is_dominate(i)) {
        if (!del || g[del].size() > g[i].size()) del = i;
      }
    if (del) {
      cout << "1\n" << del << '\n';
      return;
    }
  }
  for (auto &&[k, v] : lst)
    if (v.size() == 2) {
      cout << "2\n" << v[0] << ' ' << v[1] << '\n';
      return;
    }
  if (lst.size() > 2) {
    cout << "2\n1 ";
    for_(i, 2, n) {
      if (dsu.find(i) == dsu.find(1)) continue;
      cout << i << '\n';
      return;
    }
  }
  auto v_ = min(lst.begin()->second,
                next(lst.begin())->second,
                [&](auto const &l, auto const &r) {
                  return l.size() == r.size() ? l < r : l.size() < r.size();
                });
  cout << v_.size() << '\n';
  forit_(it, v_) cout << *it << " \n"[it == prev(v_.end())];
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  int t_ = 0;
  std::cin >> t_;
  for (i_ = 0; i_ < t_; ++i_) solve(i_);
  return 0;
}
