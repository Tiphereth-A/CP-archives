#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
const int N = 500 + 5;
using sg_t = bool[N][N];
using vis_t = bool[N][N];
char maps[N][N];
const pii DIR[2] = {{0, 1}, {1, 0}};
int n, m;
auto valid(int x, int y) -> bool { return x > 0 && y > 0 && x <= n && y <= m; }
bool dfs(sg_t &sg, vis_t &vis, int x, int y) {
  if (vis[x][y]) return sg[x][y];
  vis[x][y] = 1;
  vector<bool> res;
  for (auto &&[dx, dy] : DIR) {
    auto nowx = x + dx, nowy = y + dy;
    if (!valid(nowx, nowy)) continue;
    res.push_back(dfs(sg, vis, nowx, nowy));
  }
  return sg[x][y] = any_of(res.begin(),
                           res.end(),
                           [&](bool b) { return b ^ ((x + y) & 1); }) ^
                    ((x + y) & 1);
}
void clear(sg_t &sg, vis_t vis) {
  for (int i = 1; i <= n; ++i) memset(sg[i], 0, sizeof(sg[0][0]) * (m + 1));
  for (int i = 1; i <= n; ++i) memset(vis[i], 0, sizeof(vis[0][0]) * (m + 1));
}
sg_t sga, sgb, sgc;
vis_t visa, visb, visc;
const string resyn[2] = {"no", "yes"};
int main() {
  int t;
  cin >> t;
  for (; t; t--) {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> (maps[i] + 1);
    clear(sga, visa);
    clear(sgb, visb);
    clear(sgc, visc);
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j) {
        if (maps[i][j] == '.') continue;
        (maps[i][j] == 'A' ? sga : sgb)[i][j] = 1;
        visa[i][j] = visb[i][j] = visc[i][j] = 1;
      }
    if (maps[n][m] == '.') sgc[n][m] = visa[n][m] = visb[n][m] = visc[n][m] = 1;
    bool win = dfs(sga, visa, 1, 1);
    bool lose = dfs(sgb, visb, 1, 1);
    bool draw = dfs(sgc, visc, 1, 1);
    cout << resyn[win] << ' ' << resyn[draw] << ' ' << resyn[lose] << '\n';
  }
  return 0;
}
