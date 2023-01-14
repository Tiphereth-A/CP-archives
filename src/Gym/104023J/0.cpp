#include <bits/stdc++.h>
using ll = long long;
using pii = std::pair<int, int>;
using namespace std;
const int N = 100010;
int a[N];
void solve(int t_ = 0) {
  int n, k;
  cin >> n >> k;
  ll ss = 0;
  for (int i = 1; i <= n; ++i) cin >> a[i], ss += a[i];
  vector<pii> cons;
  priority_queue<int, vector<int>, greater<int>> lim;
  for (int i = 1; i <= k; ++i) {
    int x, y;
    cin >> x >> y;
    if (y == 0) lim.push(x);
    else cons.emplace_back(x, y);
  }
  lim.push(1e9);
  a[n + 1] = 1e9 + 1;
  sort(a + 1, a + n + 2);
  sort(cons.begin(), cons.end());
  int now = 0, cnt = 0;
  ll sum = 0;
  while (!lim.empty() && lim.top() == now) ++now, lim.pop();
  auto it = cons.begin();
  while (!lim.empty()) {
    int nxt = upper_bound(a + 1, a + n + 2, lim.top()) - a;
    int count1 = nxt - (lower_bound(a + 1, a + n + 2, now) - a);
    while (count1 && it != cons.end() && it->first < lim.top() &&
           it->first == now) {
      sum += min(count1, it->second) * it->first;
      count1 -= min(count1, it->second);
      ++now;
      ++it;
    }
    sum += count1 * now;
    while (it != cons.end() && it->first < lim.top()) { ++it; }
    now = lim.top();
    while (!lim.empty() && lim.top() == now) ++now, lim.pop();
  }
  int count1 = n + 1 - (lower_bound(a + 1, a + n + 2, now) - a);
  while (count1 && it != cons.end() && it->first < lim.top() &&
         it->first == now) {
    sum += min(count1, it->second) * it->first;
    count1 -= min(count1, it->second);
    ++now;
    ++it;
  }
  sum += now * count1;
  if ((ss - sum) & 1) cout << "Pico\n";
  else cout << "FuuFuu\n";
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  int t_ = 0;
  std::cin >> t_;
  for (i_ = 0; i_ < t_; ++i_) solve(i_);
  return 0;
}
