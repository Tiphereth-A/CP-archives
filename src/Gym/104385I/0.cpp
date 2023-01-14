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
  int n, q;
  cin >> n >> q;
  vc<int> val(n + 1);
  for_(i, 1, n - 1, u, v, w) {
    cin >> u >> v >> w;
    val[v] ^= w;
    val[u] ^= w;
  }
  for_(i, 1, q, op, x, y, z) {
    cin >> op >> x;
    if (op == 1) {
      cin >> y >> z;
      val[x] ^= z;
      val[y] ^= z;
    } else cout << val[x] << '\n';
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
