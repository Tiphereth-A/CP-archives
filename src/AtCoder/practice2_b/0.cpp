#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#include <atcoder/fenwicktree.hpp>
using namespace atcoder;
int main() {
  int n, q;
  cin >> n >> q;
  fenwick_tree<i64> tr(n);
  for (int i = 0, a; i < n; ++i) {
    cin >> a;
    tr.add(i, a);
  }
  for (int t, x, y; q; --q) {
    cin >> t >> x >> y;
    if (t) cout << tr.sum(x, y) << '\n';
    else tr.add(x, y);
  }
  return 0;
}
