#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<pii> v;
    for (int i = 0, x; i < n; ++i) {
      cin >> x;
      v.emplace_back(x, i);
    }
    sort(v.begin(), v.end());
    if (v.front().first == v.back().first) {
      cout << "NO\n";
      continue;
    }
    vector<int> ans(n);
    vector<bool> vis(n);
    vector<pii> vp2 = v;
    vp2.erase(unique(vp2.begin(),
                     vp2.end(),
                     [](const auto &lhs, const auto &rhs) {
                       return lhs.first == rhs.first;
                     }),
              vp2.end());
    vp2.push_back(vp2.front());
    for (auto it = vp2.begin() + 1; it != vp2.end(); ++it) {
      ans[(it - 1)->second] = it->first;
      vis[it->first] = true;
    }
    for (int i = 0, now = 1; i < n; ++i) {
      if (ans[i]) continue;
      while (vis[now]) ++now;
      ans[i] = now++;
    }
    cout << "YES\n";
    for (auto &&i : ans) cout << i << ' ';
    cout << '\n';
  }
  return 0;
}
