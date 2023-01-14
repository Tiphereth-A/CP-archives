#include <bits/stdc++.h>
const int dx[] = {1, 2, 2, 1}, dy[] = {2, 1, -1, -2};
using std::cin;
using std::cout;
int n, m;
int ans;
void dfs(int now_x, int now_y) {
  if (now_x == m && now_y == n) {
    ++ans;
    return;
  }
  for (int i = 0; i < 4; ++i) {
    int xx = now_x + dx[i], yy = now_y + dy[i];
    if (xx < 0 || xx > m || yy < 0 || yy > n) continue;
    dfs(xx, yy);
  }
}
int main() {
  cin >> n >> m;
  dfs(0, 0);
  std::cout << ans;
  return 0;
}
