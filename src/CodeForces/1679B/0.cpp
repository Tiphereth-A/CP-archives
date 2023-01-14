#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
struct Query {
  int l, r;
} q[M];
map<int, int> mp;
auto solve() -> void {
  int n, m;
  cin >> n >> m;
  i64 ans = 0;
  int global_a = 0;
  _for(i, 1, n, x) {
    cin >> x;
    mp[i] = x;
    ans += x;
  }
  _for(i, 1, m, t, x, y) {
    cin >> t >> x;
    if (t == 2) {
      global_a = x;
      ans = 1ll * n * x;
      mp.clear();
    } else {
      cin >> y;
      if (mp[x]) {
        ans += y - mp[x];
      } else {
        ans += y - global_a;
      }
      mp[x] = y;
    }
    cout << ans << '\n';
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
