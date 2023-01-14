#include <bits/stdc++.h>
using ll = long long;
template <class Tp>
using vc = std::vector<Tp>;
#define for_(i, l, r, v...) for (ll i = (l), i##e = (r), ##v; i <= i##e; ++i)
template <class Tp>
Tp dec(Tp &i) {
  return --i;
}
template <class Tp>
Tp inc(Tp &i) {
  return ++i;
}
using namespace std;
void solve(int t_ = 0) {
  int n;
  cin >> n;
  vc<int> a(n);
  for (auto &i : a) cin >> i;
  int ans = 0;
  for_(__, 1, 32) {
    n = a.size();
    if (n <= 1) break;
    ++ans;
    if (n <= 2) break;
    vc<bool> vis(n);
    vis[0] = a[0] < a[1];
    vis[n - 1] = a[n - 1] < a[n - 2];
    for_(i, 1, n - 2) vis[i] = a[i] < a[i - 1] || a[i] < a[i + 1];
    vc<int> b;
    for_(i, 0, n - 1)
      if (!vis[i]) b.push_back(a[i]);
    a = b;
  }
  cout << ans << '\n';
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  solve(i_);
  return 0;
}
