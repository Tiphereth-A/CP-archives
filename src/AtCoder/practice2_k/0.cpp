#include <bits/stdc++.h>
using namespace std;
#include <atcoder/lazysegtree.hpp>
#include <atcoder/modint.hpp>
using namespace atcoder;
struct S {
  modint998244353 dt;
  int sz;
};
struct F {
  modint998244353 a, b;
};
auto op(S lhs, S rhs) -> S { return S{lhs.dt + rhs.dt, lhs.sz + rhs.sz}; }
auto e() -> S { return S{0, 0}; }
auto mapping(F f, S x) -> S { return S{x.dt * f.a + x.sz * f.b, x.sz}; }
auto composition(F f, F g) -> F { return F{g.a * f.a, g.b * f.a + f.b}; }
auto id() -> F { return F{1, 0}; }
int main() {
  int n, q;
  cin >> n >> q;
  vector<S> a(n);
  int x;
  for (auto &i : a) {
    cin >> x;
    i = {x, 1};
  }
  lazy_segtree<S, op, e, F, mapping, composition, id> tr(a);
  for (int t, x, y, b, c; q; --q) {
    cin >> t >> x >> y;
    switch (t) {
      case 0:
        cin >> b >> c;
        tr.apply(x, y, F{b, c});
        break;
      case 1: cout << tr.prod(x, y).dt.val() << '\n'; break;
      default: throw runtime_error("やだもやだ、無理も無理");
    }
  }
  return 0;
}
