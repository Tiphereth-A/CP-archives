#include <bits/stdc++.h>
using ll = long long;
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

public:
  std::set<Node> data;

public:
  Chtholly(): data() {}
  explicit Chtholly(std::vector<Tp> const &c): Chtholly() {
    size_t cnt = 0;
    for (auto &&i : c) {
      data.emplace(cnt, cnt, i);
      ++cnt;
    }
  }
  void clear() { data.clear(); }
  void insert(size_t l, size_t r, Tp const &v) { data.emplace(l, r, v); }
  auto find(size_t x) const {
    return std::prev(data.upper_bound(Node{x, 0, 0}));
  }
  auto split(size_t x) {
    auto it = find(x);
    if (it->l == x) return it;
    auto [l, r, v] = *it;
    data.erase(it);
    data.emplace(l, x - 1, v);
    return data.emplace(x, r, v).first;
  }
  void assign(size_t l, size_t r, Tp const &v) {
    auto itr = split(r + 1), itl = split(l);
    data.erase(itl, itr);
    data.emplace(l, r, v);
  }
  void assign_and_merge(size_t l, size_t r, Tp const &v) {
    auto itl = find(l), itr = find(r);
    if (itr != data.end()) {
      if (itr != std::prev(data.end()) && itr->r == r && (++itr)->v == v)
        r = (itr++)->r;
      else if (itr->v != v) {
        itr = split(r + 1);
        itl = find(l);
      } else r = (itr++)->r;
    }
    if (itl != data.begin() && itr->l == l && std::prev(itl)->v == v)
      l = (--itl)->l;
    else if (itl->v != v) itl = split(l);
    else l = itl->l;
    data.erase(itl, itr);
    data.emplace(l, r, v);
  }
  template <class Func>
  void run(size_t l, size_t r, Func func) {
    for (auto itr = split(r + 1), itl = split(l); itl != itr; ++itl) func(itl);
  }
  template <class Func>
  auto run_no_split(size_t l, size_t r, Func func) const {
    return func(find(l), find(r));
  }
};
void solve(int t_ = 0) {
  int n, m;
  cin >> n >> m;
  Chtholly<int> odt;
  odt.insert(1, n, 0);
  for_(i, 1, m, l, r) {
    cin >> l >> r;
    odt.assign(l, r, i);
  }
  set<int> res;
  for (auto &&k : odt.data) res.insert(k.v);
  cout << res.size() - !!res.count(0) << '\n';
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  solve(i_);
  return 0;
}
