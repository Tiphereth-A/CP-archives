#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
const int N = 1e3 + 5;
const pii DIR8[8] = {
  {-1, -2}, {-1, 2}, {1, 2}, {1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};
int vis[N][N];
bool target[N][N];
pii query[N * N];
auto vaild = [](int x, int y, int n, int m) -> bool {
  return (x >= 1) && (x <= n) && (y >= 1) && (y <= m);
};
auto solve() -> void {
  int n, m, q;
  cin >> n >> m >> q;
  int x, y;
  cin >> x >> y;
  _for(i, 1, q, x, y) {
    cin >> x >> y;
    target[x][y] = 1;
    query[i] = {x, y};
  }
  queue<tuple<int, int, int>> pos;
  pos.emplace(x, y, 1);
  vis[x][y] = 1;
  int cnt = 0;
  while (cnt < q && !pos.empty()) {
    auto [x, y, step] = pos.front();
    pos.pop();
    for (auto [dx, dy] : DIR8) {
      if (!vaild(x + dx, y + dy, n, m)) continue;
      if (vis[x + dx][y + dy]) continue;
      if (target[x + dx][y + dy]) ++cnt;
      vis[x + dx][y + dy] = step;
      pos.emplace(x + dx, y + dy, step + 1);
    }
  }
  _for(i, 1, q)
    cout << (query[i].first == x && query[i].second == y ?
               0 :
             vis[query[i].first][query[i].second] ?
               vis[query[i].first][query[i].second] :
               -1)
         << '\n';
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
