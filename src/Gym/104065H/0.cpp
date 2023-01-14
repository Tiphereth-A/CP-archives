#include <bits/stdc++.h>
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
  int k;
  cin >> k;
  k = 2 * k - 1;
  cout << k << '\n';
  int x = 1;
  while (k--) {
    cout << x << ' ' << x << '\n';
    inc(x);
  }
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  solve(i_);
  return 0;
}
