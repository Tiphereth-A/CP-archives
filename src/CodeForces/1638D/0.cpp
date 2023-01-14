#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _all(a) (a).begin(), (a).end()
#define _run_return_void(expressions) \
  {                                   \
    expressions;                      \
    return;                           \
  }
#define _run_continue(expressions) \
  {                                \
    expressions;                   \
    continue;                      \
  }
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
const uint32_t OFFSET = 5;
const uint32_t N = 1000 + OFFSET, M = 2e5 + OFFSET, K = 21;
const pii DIR8[8] = {
  {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
int maps[N][N];
bool inq[N][N];
int n, m;
auto valid = [](int x, int y) -> int {
  if (x < 1 || x >= n || y < 1 || y >= m) return 0;
  if (inq[x][y]) return 0;
  int _ = 0;
  for (auto i :
       {maps[x][y], maps[x][y + 1], maps[x + 1][y], maps[x + 1][y + 1]}) {
    if (!i) continue;
    if (!_) _run_continue(_ = i);
    if (_ != i) return 0;
  }
  return _;
};
auto set_null = [](int x, int y) -> void {
  if (x < 1 || x >= n || y < 1 || y >= m) return;
  maps[x][y] = maps[x][y + 1] = maps[x + 1][y] = maps[x + 1][y + 1] = 0;
};
auto solve() -> void {
  cin >> n >> m;
  _for(i, 1, n)
    _for(j, 1, m) cin >> maps[i][j];
  queue<tuple<int, int, int>> q;
  vector<tuple<int, int, int>> ans;
  _for(i, 1, n - 1)
    _for(j, 1, m - 1)
      if (valid(i, j)) {
        q.emplace(i, j, maps[i][j]);
        inq[i][j] = 1;
      }
  int cnt = 0;
  while (!q.empty()) {
    if (++cnt > n * m) _run_return_void(cout << "-1\n");
    auto [x, y, c] = q.front();
    ans.emplace_back(x, y, c);
    set_null(x, y);
    for (auto [dx, dy] : DIR8)
      if (int now_x = x + dx, now_y = y + dy, now_c = valid(now_x, now_y);
          now_c) {
        q.emplace(now_x, now_y, now_c);
        inq[now_x][now_y] = 1;
      }
    q.pop();
  }
  _for(i, 1, n)
    _for(j, 1, m)
      if (maps[i][j]) _run_return_void(cout << "-1\n");
  reverse(_all(ans));
  cout << ans.size() << '\n';
  for (auto [x, y, c] : ans) cout << x << ' ' << y << ' ' << c << '\n';
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
