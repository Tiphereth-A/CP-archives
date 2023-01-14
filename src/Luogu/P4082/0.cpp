#include <bits/stdc++.h>
using namespace std;
using u32 = uint32_t;
u32 n, m;
vector<string> mp;
bool outbound(pair<int, int> const &p) {
  return p.first < 0 || p.second < 0 || p.first >= n || p.second >= m;
}
namespace bcc {
const int N = 1505, mov[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
int idx, cnt, dfn[N][N], low[N][N], belongs[N][N][5];
vector<pair<int, int>> stk;
void upd(int x, int y, int id) { belongs[x][y][++belongs[x][y][0]] = id; }
void tarjan(int x, int y, int fax, int fay) {
  dfn[x][y] = low[x][y] = ++idx;
  stk.emplace_back(x, y);
  for (int i = 0; i < 4; ++i) {
    int nx = x + mov[i][0], ny = y + mov[i][1];
    if (outbound({nx, ny}) || mp[nx][ny] == '#') continue;
    if (!dfn[nx][ny]) {
      tarjan(nx, ny, x, y);
      if (low[nx][ny] >= dfn[x][y]) {
        upd(x, y, ++cnt);
        while (stk.back().first != nx || stk.back().second != ny) {
          upd(stk.back().first, stk.back().second, cnt);
          stk.pop_back();
        }
        upd(nx, ny, cnt);
        stk.pop_back();
      }
      low[x][y] = min(low[x][y], low[nx][ny]);
    } else if (dfn[x][y] > dfn[nx][ny] && (nx != fax || ny != fay))
      low[x][y] = min(low[x][y], dfn[nx][ny]);
  }
}
bool same_bcc(pair<int, int> const &s, pair<int, int> const &t) {
  int x1 = s.first, y1 = s.second, x2 = t.first, y2 = t.second;
  for (int i = 1; i <= belongs[x1][y1][0]; ++i)
    for (int j = 1; j <= belongs[x2][y2][0]; ++j)
      if (belongs[x1][y1][i] == belongs[x2][y2][j]) return true;
  return false;
}
}  // namespace bcc
map<pair<int, int>, u32> encode;
vector<pair<int, int>> decode{{-1, -1}};
pair<int, int> S, T;
namespace search {
const pair<int, int> diff[4]{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
vector<u32> valid_dir;
void bfs1() {
  queue<pair<int, int>> q;
  vector<vector<bool>> vis(n + 1, vector<bool>(m + 1));
  q.push(S);
  vis[S.first][S.second] = 1;
  while (!q.empty()) {
    auto now = q.front();
    q.pop();
    for (u32 i = 0; i < 4; ++i) {
      auto const &d = diff[i];
      pair<int, int> nxt{now.first + d.first, now.second + d.second};
      if (nxt == T) {
        valid_dir.push_back(i);
        continue;
      }
      if (outbound(nxt) || vis[nxt.first][nxt.second] ||
          mp[nxt.first][nxt.second] == '#')
        continue;
      vis[nxt.first][nxt.second] = 1;
      q.push(nxt);
    }
  }
}
struct Node {
  pair<int, int> from, to;
};
vector<vector<vector<bool>>> vis;
void bfs2() {
  queue<Node> q;
  vis.resize(n + 1, vector<vector<bool>>(m + 1, vector<bool>(4)));
  for (auto i : valid_dir) {
    pair<int, int> pre{T.first - diff[i].first, T.second - diff[i].second};
    q.push({pre, T});
    vis[T.first][T.second][i] = 1;
  }
  while (!q.empty()) {
    auto from = q.front().from, to = q.front().to;
    q.pop();
    for (u32 i = 0; i < 4; ++i) {
      auto const &d = diff[i];
      pair<int, int> pre{to.first - d.first, to.second - d.second};
      pair<int, int> nxt{to.first + d.first, to.second + d.second};
      if (outbound(nxt) || mp[nxt.first][nxt.second] == '#') continue;
      if (vis[nxt.first][nxt.second][i]) continue;
      if (outbound(pre) || pre != from && !bcc::same_bcc(from, pre)) continue;
      vis[nxt.first][nxt.second][i] = 1;
      q.push({to, nxt});
    }
  }
}
}  // namespace search
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  u32 q;
  cin >> n >> m >> q;
  mp.resize(n);
  for (auto &i : mp) cin >> i;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      if (mp[i][j] != '#') {
        decode.emplace_back(i, j);
        encode[decode.back()] = decode.size() - 1;
      }
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      if (mp[i][j] == 'A') S = make_pair(i, j);
      else if (mp[i][j] == 'B') T = make_pair(i, j);
  bcc::tarjan(S.first, S.second, n + 10, m + 10);
  search::bfs1();
  search::bfs2();
  for (int i = 1, u, v; i <= q; ++i) {
    cin >> u >> v;
    --u;
    --v;
    cout << (search::vis[u][v][0] || search::vis[u][v][1] ||
                 search::vis[u][v][2] || search::vis[u][v][3] ||
                 make_pair(u, v) == T ?
               "YES" :
               "NO")
         << '\n';
  }
  return 0;
}
