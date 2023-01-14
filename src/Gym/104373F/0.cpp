#include <bits/stdc++.h>
#include <queue>
#include <vector>
using ll = long long;
using pii = std::pair<int, int>;
#define for_(i, l, r, v...) for (ll i = (l), i##e = (r), ##v; i <= i##e; ++i)
#define Rep for_
template <typename... Ts>
void dec(Ts &...x) {
  ((--x), ...);
}
template <typename... Ts>
void inc(Ts &...x) {
  ((++x), ...);
}
using namespace std;
void solve(int t_ = 0) {
  int n;
  cin >> n;
  vector<int> a(n + 1);
  priority_queue<pair<int, int>> Q;
  Rep(i, 1, n) cin >> a[i], Q.emplace(a[i], i);
  bool flag = 1;
  int ret;
  Rep(i, 1, n) {
    int top = Q.top().first, id = Q.top().second;
    Q.pop();
    if (top + (i - 1) < n - 1) {
      Q.emplace(top, id);
      flag = 0;
      ret = i - 1;
      break;
    }
    top -= n;
    Q.emplace(top, id);
  }
  if (flag) cout << "Recurrent";
  else {
    vector<pair<int, int>> ans;
    while (!Q.empty()) ans.emplace_back(Q.top()), Q.pop();
    sort(
      ans.begin(), ans.end(), [](pii a, pii b) { return a.second < b.second; });
    cout << ans[0].first + ret;
    Rep(i, 1, ans.size() - 1) cout << ' ' << ans[i].first + ret;
  }
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  solve(i_);
  return 0;
}
