#include <bits/stdc++.h>
struct DSUWeighted {
  struct Node {
    size_t fa, dep, sz;
    explicit Node(size_t fa, size_t depth = 0, size_t size = 1)
      : fa(fa), dep(dep), sz(size) {}
  };
  std::vector<Node> data;
  DSUWeighted() = default;
  void init(size_t n) {
    data.clear();
    data.reserve(n);
    data.shrink_to_fit();
    for (size_t i = 0; i < n; ++i) data.emplace_back(i);
  }
  size_t find(size_t x) {
    if (x == data[x].fa) return x;
    size_t fx = find(data[x].fa);
    data[x].dep += data[data[x].fa].dep;
    return data[x].fa = fx;
  }
  void merge(size_t x, size_t y) {
    size_t fx = find(x), fy = find(y);
    data[fx].dep += data[fy].sz;
    data[fy].sz += data[fx].sz;
    data[fx].sz = 0;
    data[fx].fa = fy;
  }
};
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  DSUWeighted dsu;
  dsu.init(3e4 + 1);
  int t;
  cin >> t;
  char op;
  while (t--) {
    int x, y;
    cin >> op >> x >> y;
    if (op == 'M') {
      dsu.merge(x, y);
      continue;
    }
    cout << (dsu.find(x) != dsu.find(y) ?
               -1 :
               abs(ptrdiff_t(dsu.data[x].dep) - ptrdiff_t(dsu.data[y].dep)) - 1)
         << '\n';
  }
  return 0;
}
