#include <bits/stdc++.h>
using namespace std;
using node = tuple<int, int, int>;
int main() {
  int n;
  string s;
  cin >> n >> s;
  vector<bool> f(n), vis(n);
  transform(s.begin(), s.end(), f.begin(), [](char ch) { return ch == 'B'; });
  vector<int> q(n);
  for (int i = 0; i < n; ++i) cin >> q[i];
  priority_queue<node, vector<node>, greater<node>> pq;
  for (int i = 0; i < n - 1; ++i)
    if (f[i] != f[i + 1]) pq.emplace(abs(q[i] - q[i + 1]), i, i + 1);
  vector<pair<int, int>> ans;
  ans.reserve(n / 2 + 1);
  while (!pq.empty()) {
    auto [ignore, x, y] = pq.top();
    pq.pop();
    if (!vis[x] && !vis[y]) {
      vis[x] = vis[y] = true;
      ans.emplace_back(x, y);
      while (x >= 0 && vis[x]) --x;
      while (y < n && vis[y]) ++y;
      if (x >= 0 && y < n && f[x] != f[y]) pq.emplace(abs(q[x] - q[y]), x, y);
    }
  }
  cout << ans.size() << '\n';
  for (auto &&[x, y] : ans) cout << x + 1 << ' ' << y + 1 << '\n';
  return 0;
}
