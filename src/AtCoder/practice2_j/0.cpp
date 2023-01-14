#include <bits/stdc++.h>
using namespace std;
#include <atcoder/segtree.hpp>
using namespace atcoder;
auto op(int a, int b) -> int { return max(a, b); }
auto e() -> int { return -1; }
int main() {
  int n, q;
  cin >> n >> q;
  vector<int> a(n);
  for (auto &i : a) cin >> i;
  segtree<int, op, e> tr(a);
  for (int t, x, y; q; --q) {
    cin >> t >> x >> y;
    --x;
    switch (t) {
      case 1: tr.set(x, y); break;
      case 2: cout << tr.prod(x, y) << '\n'; break;
      case 3:
        cout << tr.max_right(x, [&](int _) { return _ < y; }) + 1 << '\n';
        break;
      default: throw runtime_error("やだもヤダ、無理も無理");
    }
  }
  return 0;
}
