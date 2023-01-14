#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1000 + 5;
ll c, ans, a[N], sum[N];
void dfs(int now, ll x) {
  if (x > c) return;
  if (sum[now - 1] + x <= c) {
    ans = max(ans, sum[now - 1] + x);
    return;
  }
  ans = max(ans, x);
  for (int i = 1; i < now; ++i) dfs(i, x + a[i]);
};
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  cin >> n >> c;
  for (ll i = 1, x; i <= n; ++i) {
    cin >> x;
    if (x > c) {
      n = i - 1;
      break;
    } else a[i] = x;
  }
  for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + a[i];
  dfs(n + 1, 0);
  cout << ans << '\n';
  return 0;
}
