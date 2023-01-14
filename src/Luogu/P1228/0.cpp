#include <bits/stdc++.h>
using namespace std;
vector<tuple<int, int, int>> ans;
void dc(int mapx, int mapy, int ocpx, int ocpy, int dep) {
  if (dep == 0) return;
  int len = 1 << (dep - 1);
  int mx = mapx + len, my = mapy + len;
  if (ocpx < mx && ocpy < my) {
    dc(mapx, mapy, ocpx, ocpy, dep - 1);
    dc(mapx, my, mx - 1, my, dep - 1);
    dc(mx, mapy, mx, my - 1, dep - 1);
    dc(mx, my, mx, my, dep - 1);
    ans.emplace_back(mx, my, 1);
    return;
  }
  if (ocpx < mx && ocpy >= my) {
    dc(mapx, mapy, mx - 1, my - 1, dep - 1);
    dc(mapx, my, ocpx, ocpy, dep - 1);
    dc(mx, mapy, mx, my - 1, dep - 1);
    dc(mx, my, mx, my, dep - 1);
    ans.emplace_back(mx, my - 1, 2);
    return;
  }
  if (ocpx >= mx && ocpy < my) {
    dc(mapx, mapy, mx - 1, my - 1, dep - 1);
    dc(mapx, my, mx - 1, my, dep - 1);
    dc(mx, mapy, ocpx, ocpy, dep - 1);
    dc(mx, my, mx, my, dep - 1);
    ans.emplace_back(mx - 1, my, 3);
    return;
  }
  dc(mapx, mapy, mx - 1, my - 1, dep - 1);
  dc(mapx, my, mx - 1, my, dep - 1);
  dc(mx, mapy, mx, my - 1, dep - 1);
  dc(mx, my, ocpx, ocpy, dep - 1);
  ans.emplace_back(mx - 1, my - 1, 4);
}
auto solve(int t_ = 0) -> void {
  int k, x, y;
  cin >> k >> x >> y;
  ans.reserve(((1 << (2 * k)) - 1) / 3);
  dc(1, 1, x, y, k);
  for (auto &&[x, y, c] : ans) cout << x << ' ' << y << ' ' << c << '\n';
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
