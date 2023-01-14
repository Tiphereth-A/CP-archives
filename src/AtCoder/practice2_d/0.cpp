#include <bits/stdc++.h>
using namespace std;
#include <atcoder/maxflow.hpp>
using namespace atcoder;
int main() {
  int n, m;
  cin >> n >> m;
  vector<string> maps(n);
  for (auto &i : maps) cin >> i;
  mf_graph<int> g(n * m + 2);
  int s = n * m, t = s + 1;
  auto encode = [&](int i, int j) { return i * m + j; };
  auto decode = [&](int x) -> pair<int, int> { return {x / m, x % m}; };
  for (int i = 0, v; i < n; ++i)
    for (int j = 0; j < m; ++j) {
      if (maps[i][j] == '#') continue;
      v = encode(i, j);
      g.add_edge((i + j) & 1 ? v : s, (i + j) & 1 ? t : v, 1);
    }
  for (int i = 0, v; i < n; ++i)
    for (int j = 0; j < m; ++j) {
      if ((i + j) & 1 || maps[i][j] == '#') continue;
      v = encode(i, j);
      if (i && maps[i - 1][j] == '.') g.add_edge(v, encode(i - 1, j), 1);
      if (j && maps[i][j - 1] == '.') g.add_edge(v, encode(i, j - 1), 1);
      if (i + 1 < n && maps[i + 1][j] == '.')
        g.add_edge(v, encode(i + 1, j), 1);
      if (j + 1 < m && maps[i][j + 1] == '.')
        g.add_edge(v, encode(i, j + 1), 1);
    }
  cout << g.flow(s, t) << '\n';
  for (auto &&[from, to, ignore, flow] : g.edges()) {
    if (from == s || to == t || !flow) continue;
    auto &&[x1, y1] = decode(from);
    auto &&[x2, y2] = decode(to);
    if (x1 == x2 - 1) {
      maps[x1][y1] = 'v';
      maps[x2][y2] = '^';
      continue;
    }
    if (x1 == x2 + 1) {
      maps[x1][y1] = '^';
      maps[x2][y2] = 'v';
      continue;
    }
    if (y1 == y2 - 1) {
      maps[x1][y1] = '>';
      maps[x2][y2] = '<';
      continue;
    }
    if (y1 == y2 + 1) {
      maps[x1][y1] = '<';
      maps[x2][y2] = '>';
      continue;
    }
  }
  for (auto &&s : maps) cout << s << '\n';
  return 0;
}
