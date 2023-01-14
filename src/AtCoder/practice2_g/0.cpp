#include <bits/stdc++.h>
using namespace std;
#include <atcoder/scc.hpp>
using namespace atcoder;
int main() {
  int n, m;
  cin >> n >> m;
  scc_graph scc(n);
  for (int a, b; m; --m) {
    cin >> a >> b;
    scc.add_edge(a, b);
  }
  auto __ = scc.scc();
  cout << __.size() << '\n';
  for (auto &&_ : __) {
    cout << _.size();
    for (auto &&i : _) cout << ' ' << i;
    cout << '\n';
  }
  return 0;
}
