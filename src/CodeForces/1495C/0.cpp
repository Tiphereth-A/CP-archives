#include <bits/stdc++.h>
using ll = long long;
template <class Tp>
using vc = std::vector<Tp>;
#define for_(i, l, r, v...) for (ll i = (l), i##e = (r), ##v; i <= i##e; ++i)
#define fors_(i, l, r, s, v...) \
  for (ll i = (l), i##e = (r), ##v; i <= i##e; i += s)
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
  int n, m;
  cin >> n >> m;
  vc<string> mp(n);
  for (auto &i : mp) cin >> i;
  if (m == 1) {
    for_(i, 1, n) cout << "X\n";
    return;
  }
  if (n == 1) {
    for_(i, 1, m) cout << 'X';
    cout << '\n';
    return;
  }
  fors_(i, m % 3 == 0, m - 1, 3)
    for (auto &j : mp) j[i] = 'X';
  fors_(i, 1 + (m % 3 == 0), m - 1, 3) {
    if (i + 1 >= m) break;
    bool f = 0;
    for (auto &j : mp)
      if (j[i] ^ j[i + 1]) {
        j[i] = j[i + 1] = 'X';
        f = 1;
        break;
      }
    if (!f) mp[0][i] = mp[0][i + 1] = 'X';
  }
  for (auto &&i : mp) cout << i << '\n';
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
