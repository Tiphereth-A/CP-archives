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

protected:
  std::set<Node> data;
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
  friend void solve(int);

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
const string YN_[2] = {"No", "Yes"};
void solve(int t_ = 0) {
  size_t n, m;
  string s;
  cin >> n >> s >> m;
  Chtholly<char> odt;
  for (size_t l = 0, r = 0; l < n; l = r) {
    while (r < n && s[++r] == s[l]);
    odt.insert(l + 1, r, s[l]);
  }
  for_(i, 1, m) {
    char op, c;
    size_t l, r;
    cin >> op >> l >> r;
    switch (op) {
      case 'A':
        cin >> c;
        odt.assign_and_merge(l, r, c);
        break;
      case 'B':
        cout << YN_[odt.run_no_split(l, r, [&](auto itl, auto itr) {
          if (itl != itr) return false;
          if (!(l != 1 && r != n)) return true;
          if (l > itl->l && r < itl->r) return false;
          if (l == itl->l && r != itl->r) return std::prev(itl)->v != itl->v;
          if (l != itl->l && r == itl->r) return std::next(itl)->v != itl->v;
          return std::prev(itl)->v != std::next(itl)->v;
        })] << '\n';
        break;
      default: break;
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
