#include <bits/stdc++.h>
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
  int assign(size_t l, size_t r, Tp const &v) {
    static int ans = 0;
    auto itr = split(r + 1), itl = split(l);
    for (auto it = itl; it != itr; ++it) ans -= it->v * (it->r - it->l + 1);
    data.erase(itl, itr);
    data.emplace(l, r, v);
    return ans += v * (r - l + 1);
  }
  template <class Func>
  void run(size_t l, size_t r, Func func) {
    for (auto itr = split(r + 1), itl = split(l); itl != itr; ++itl) func(itl);
  }
};
void solve(int t_ = 0) {
  int n, m;
  cin >> n >> m;
  Chtholly<int> odt;
  odt.insert(1, n, 1);
  for (int i = 1, l, r, k; i <= m; ++i) {
    cin >> l >> r >> k;
    cout << n + odt.assign(l, r, k - 1) << '\n';
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
