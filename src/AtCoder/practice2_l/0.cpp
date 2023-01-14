#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#include <atcoder/lazysegtree.hpp>
using namespace atcoder;
struct S {
  i64 c0, c1, ci;
};
using F = bool;
auto op(S lhs, S rhs) -> S {
  return S{lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.ci + rhs.ci + lhs.c1 * rhs.c0};
}
auto e() -> S { return S{0, 0, 0}; }
auto mapping(F f, S x) -> S {
  return f ? S{x.c1, x.c0, x.c1 * x.c0 - x.ci} : x;
}
auto composition(F f, F g) -> F { return f ^ g; }
auto id() -> F { return false; }
int main() {
  int n, q;
  cin >> n >> q;
  vector<S> a(n);
  int x;
  for (auto &i : a) {
    cin >> x;
    i = {!x, !!x, 0};
  }
  lazy_segtree<S, op, e, F, mapping, composition, id> tr(a);
  for (int t, x, y; q; --q) {
    cin >> t >> x >> y;
    --x;
    switch (t) {
      case 1: tr.apply(x, y, true); break;
      case 2: cout << tr.prod(x, y).ci << '\n'; break;
      default: throw runtime_error("やだもやだ、無理も無理");
    }
  }
  return 0;
}
