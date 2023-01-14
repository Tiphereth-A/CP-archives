#include <bits/stdc++.h>
using namespace std;
#define for_(i, l, r, vars...)                                            \
  for (std::make_signed_t<decltype(l + r)> i = (l), i##end = (r), ##vars; \
       i <= i##end;                                                       \
       ++i)
auto solve([[maybe_unused]] int t_ = 0) -> void {
  double d1, c, d2, p;
  int n;
  cin >> d1 >> c >> d2 >> p >> n;
  vector<pair<double, double>> v(n + 2);
  v.front() = {0, p};
  for_(i, 1, n) cin >> v[i].first >> v[i].second;
  v.back() = {d1, 0};
  sort(v.begin(), v.end());
  for_(i, 0, n)
    if (v[i + 1].first - v[i].first > c * d2) {
      cout << "No Solution\n";
      return;
    }
  double ans = 0, _ = 0;
  for (int i = 0, j; i <= n; i = j) {
    for (j = i + 1; j <= n + 1; ++j) {
      if (v[j].first - v[i].first > c * d2) break;
      if (v[j].second < v[i].second) {
        ans += ((v[j].first - v[i].first) / d2 - _) * v[i].second;
        _ = 0;
        goto end1__;
      }
    }
    ans += (c - _) * v[i].second;
    _ = c - (v[--j].first - v[i].first) / d2;
  end1__:;
  }
  cout << ans << '\n';
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  cout << fixed << setprecision(2);
  int i_ = 0;
  solve(i_);
  return 0;
}
