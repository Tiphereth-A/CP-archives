#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  vector<int> v(n + 1);
  for (int i = 1; i <= n; ++i) cin >> v[i];
  unordered_map<int, int> mp;
  int cnt = 0;
  long long ans = 0;
  for (int l = 1, r = 0; l <= n; ++l) {
    while (r < n && cnt < m)
      if (++mp[v[++r]] == 1) ++cnt;
    if (cnt == m) ans += n - r + 1;
    cnt -= !(--mp[v[l]]);
  }
  cout << ans << '\n';
  return 0;
}
