#include <bits/stdc++.h>
using namespace std;
vector<int> a;
vector<bool> vis;
bool dfs(int sum, int l, int now = 0, int cab = 0, int last = 0) {
  if (now >= sum / l) return 1;
  if (cab == l) return dfs(sum, l, now + 1);
  int f = 0;
  for (int i = last; i < a.size(); ++i)
    if (!vis[i] && cab + a[i] <= l && f != a[i]) {
      vis[i] = 1;
      if (dfs(sum, l, now, cab + a[i], i + 1)) return 1;
      f = a[i];
      vis[i] = 0;
      if (cab == 0 || cab + a[i] == l) return 0;
    }
  return 0;
}
int main() {
  int n;
  while ((cin >> n), n) {
    a.clear();
    int v = 0, sum = 0;
    for (int i = 1, x; i <= n; ++i) {
      cin >> x;
      a.push_back(x);
      v = max(v, x);
      sum += x;
    }
    sort(a.begin(), a.end(), greater<int>());
    for (int l = v; l <= sum; ++l) {
      if (sum % l) continue;
      vis.clear();
      vis.resize(n);
      if (dfs(sum, l)) {
        cout << l << '\n';
        break;
      }
    }
  }
  return 0;
}
