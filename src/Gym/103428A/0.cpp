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
  vc<int> deg(n + 1);
  for_(i, 1, n - 1, u, v) {
    cin >> u >> v;
    ++deg[u];
    ++deg[v];
  }
  if (any_of(deg.begin() + 1, deg.end(), [](int x) { return x > 3; })) {
    cout << "0\n";
    return;
  }
  int cnt = count_if(deg.begin() + 1, deg.end(), [](int x) { return x <= 2; });
  cout << cnt << '\n';
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  solve(i_);
  return 0;
}
