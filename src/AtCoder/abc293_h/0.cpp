#include <bits/stdc++.h>
using namespace std;
const int inf = 0x3f3f3f3f;
vector<vector<int>> g;
vector<vector<int>> f;
void dfs(int now, int fa, int k) {
  f[now][0] = f[now][1] = f[now][2] = 0;
  for (auto to : g[now])
    if (to != fa) {
      dfs(to, now, k);
      vector<int> _{inf, inf, inf};
      if (f[now][0] + f[to][1] < k) _[1] = min(_[1], max(f[now][0], f[to][1]));
      if (f[now][1] + f[to][1] < k) _[2] = min(_[2], max(f[now][1], f[to][1]));
      if (f[now][0] + f[to][2] + 1 < k)
        _[0] = min(_[0], max(f[now][0], f[to][2] + 1));
      if (f[now][1] + f[to][2] + 1 < k)
        _[1] = min(_[1], max(f[now][1], f[to][2] + 1));
      if (f[now][2] + f[to][2] + 1 < k)
        _[2] = min(_[2], max(f[now][2], f[to][2] + 1));
      f[now][0] = _[0];
      f[now][1] = min(f[now][0], _[1]);
      f[now][2] = min(f[now][1], _[2]);
    }
}
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n;
  cin >> n;
  g.resize(n + 1);
  f.resize(n + 1, vector<int>(3));
  for (int i = 1, x, y; i < n; ++i) {
    cin >> x >> y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  int l = 1, r = n, ans = 1;
  while (l <= r) {
    int mid = l + (r - l) / 2;
    dfs(1, 0, mid);
    if (f[1][2] < inf) {
      ans = mid;
      r = mid - 1;
    } else l = mid + 1;
  }
  cout << ans << '\n';
  return 0;
}
