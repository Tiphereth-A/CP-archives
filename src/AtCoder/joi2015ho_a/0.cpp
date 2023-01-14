#include <bits/stdc++.h>
using ll = long long;
using i64 = ll;
template <class Tp>
using vc = std::vector<Tp>;
#define for_(i, l, r, v...) for (ll i = (l), i##e = (r), ##v; i <= i##e; ++i)
using namespace std;
void solve(int t_ = 0) {
  int n, m;
  cin >> n >> m;
  vc<int> diff(n + 1);
  for_(i, 1, m, p, pre = 0) {
    cin >> p;
    if (pre) {
      ++diff[min(p, pre)];
      --diff[max(p, pre)];
    }
    pre = p;
  }
  partial_sum(diff.begin(), diff.end(), diff.begin());
  i64 ans = 0;
  for_(i, 1, n, a, b, c) {
    cin >> a >> b >> c;
    ans += min(a * diff[i], c + b * diff[i]);
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
