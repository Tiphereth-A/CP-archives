#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5;
int n, a[N];
ll f(ll im) {
  ll ans = 0, sum = 0;
  for (int i = 1; i <= n; ++i) {
    sum = max(sum + a[i], (ll)0);
    if (sum >= im) {
      sum = 0;
      ++ans;
    }
  }
  return ans;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int k;
  cin >> n >> k;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  ll l = 1, r = 1e18, ans1 = -1, ans2 = -1;
  while (l <= r) {
    ll mid = r - (r - l) / 2, _ = f(mid);
    if (_ <= k) {
      r = mid - 1;
      if (_ == k) ans1 = mid;
    } else l = mid + 1;
  }
  l = 1, r = 1e18;
  while (l <= r) {
    ll mid = r - (r - l) / 2, _ = f(mid);
    if (_ >= k) {
      l = mid + 1;
      if (_ == k) ans2 = mid;
    } else r = mid - 1;
  }
  if (ans1 == -1) cout << "-1\n";
  else cout << ans1 << ' ' << ans2 << '\n';
  return 0;
}
