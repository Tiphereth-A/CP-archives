#include <bits/stdc++.h>
using ll = long long;
#define for_(i, l, r, v...) for (ll i = (l), i##e = (r), ##v; i <= i##e; ++i)
#define Rep for_
template <class Tp>
Tp dec(Tp &i) {
  return --i;
}
template <class Tp>
Tp inc(Tp &i) {
  return ++i;
}
using namespace std;
#define int long long
void exgcd(int a, int b, int &x, int &y) {
  if (b == 0) {
    x = 1, y = 0;
    return;
  }
  exgcd(b, a % b, y, x);
  y -= (a / b) * x;
}
void solve(int t_ = 0) {
  int n, m, a, b, c = 0;
  cin >> n >> m;
  Rep(i, 0, n - 1) cin >> a, c += a;
  a = n, b = n * (n + 1) / 2;
  int g1 = gcd(a, b), g2 = gcd(g1, m), ans = c % g2;
  int x, y;
  exgcd(g1, m, x, y);
  int k = ((ans - c) / g2) % m * x % m;
  exgcd(a, b, x, y);
  cout << ans << '\n';
  cout << (x * k % m + m) % m << ' ' << (y * k % m + m) % m;
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  solve(i_);
  return 0;
}
