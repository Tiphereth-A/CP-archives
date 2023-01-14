#include <bits/stdc++.h>
using namespace std;
using u32 = uint32_t;
u32 n;
struct EW {
  u32 to, inv;
};
vector<vector<EW>> g;
void ae(u32 u, u32 v) {
  if (u == v) return;
  u32 _1 = g[u].size(), _2 = g[v].size();
  g[u].push_back({v, _2});
  g[v].push_back({u, _1});
}
u32 cnt, id;
vector<u32> dfn, low;
vector<bool> cut;
vector<vector<u32>> belongs;
vector<u32> s;
void dfs(u32 u, u32 fa, u32 inv_from) {
  dfn[u] = low[u] = cnt++;
  if (u == fa && g[u].empty()) {
    cut[u] = 1;
    belongs.push_back(vector<u32>(1, u));
    ++id;
  }
  s.push_back(u);
  for (u32 i = 0; i < g[u].size(); ++i) {
    auto v = g[u][i];
    if (v.to == fa && i == inv_from) continue;
    if (dfn[v.to] == n) {
      dfs(v.to, u, v.inv);
      low[u] = min(low[u], low[v.to]);
      if (low[v.to] >= dfn[u]) {
        u32 p;
        cut[u] = 1;
        belongs.push_back(vector<u32>(1, u));
        do {
          p = s.back();
          s.pop_back();
          belongs[id].push_back(p);
        } while (p != v.to);
        ++id;
      }
    } else low[u] = min(low[u], dfn[v.to]);
  }
}
void build_vbcc() {
  cnt = id = 0;
  dfn = low = vector<u32>(n, n);
  cut = vector<bool>(n, 0);
  for (u32 i = 0; i < n; ++i)
    if (dfn[i] == n) dfs(i, i, -1);
}
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  u32 m;
  cin >> n >> m;
  g.resize(n);
  for (u32 i = 1, u, v; i <= m; ++i) {
    cin >> u >> v;
    ae(u - 1, v - 1);
  }
  build_vbcc();
  cout << id << '\n';
  for (auto const &i : belongs) {
    cout << i.size();
    for (auto j : i) cout << ' ' << j + 1;
    cout << '\n';
  }
  return 0;
}
