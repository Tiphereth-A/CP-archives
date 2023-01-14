#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const i64 N = 1e9;
#include <atcoder/mincostflow.hpp>
using namespace atcoder;
int main() {
  int n, k;
  cin >> n >> k;
  mcf_graph<int, i64> g(n * 2 + 2);
  int s = n * 2, t = s + 1;
  g.add_edge(s, t, n * k, N);
  i64 _;
  for (int i = 0; i < n; ++i) {
    g.add_edge(s, i, k, 0);
    g.add_edge(n + i, t, k, 0);
    for (int j = 0; j < n; ++j) {
      cin >> _;
      g.add_edge(i, j + n, 1, N - _);
    }
  }
  auto &&[ignore, cost] = g.flow(s, t, n * k);
  cout << N * n * k - cost << '\n';
  vector<string> ans(n, string(n, '.'));
  for (auto &&[from, to, ignore, flow, cost] : g.edges()) {
    if (from == s || to == t || !flow) continue;
    ans[from][to - n] = 'X';
  }
  for (auto &&i : ans) cout << i << '\n';
  return 0;
}
