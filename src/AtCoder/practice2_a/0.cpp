#include <bits/stdc++.h>
using namespace std;
#include <atcoder/dsu.hpp>
using namespace atcoder;
int main() {
  int n, q;
  cin >> n >> q;
  dsu d(n);
  for (int t, x, y; q; --q) {
    cin >> t >> x >> y;
    if (t) cout << d.same(x, y) << '\n';
    else d.merge(x, y);
  }
  return 0;
}
