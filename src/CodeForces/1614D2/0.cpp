#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int &i : a) cin >> i;
  int maxa = *max_element(a.begin(), a.end());
  vector<int> p;
  {
    vector<bool> vis(maxa + 1);
    p.reserve(maxa / 10);
    for (int i = 2; i <= maxa; ++i) {
      if (!vis[i]) p.push_back(i);
      for (int j : p) {
        if (1ll * i * j > maxa) break;
        vis[i * j] = 1;
        if (i % j == 0) break;
      }
    }
  }
  vector<int> cnt(maxa + 1);
  for (int i : a)
    for (int j = 1; j * j <= i; ++j)
      if (i % j == 0) {
        ++cnt[j];
        if (i / j != j) ++cnt[i / j];
      }
  vector<i64> f(maxa + 1);
  for (int i = maxa; i >= 1; --i) {
    f[i] = 1ll * i * cnt[i];
    if (!f[i]) continue;
    for (int j : p) {
      if (1ll * i * j > maxa) break;
      if (f[i * j])
        f[i] = max(f[i], f[i * j] + 1ll * i * (cnt[i] - cnt[i * j]));
    }
  }
  i64 ans = 0;
  for (int i = 1; i <= maxa; ++i)
    if (cnt[i] == n) ans = max(ans, f[i]);
  cout << ans << '\n';
  return 0;
}
