#include <bits/stdc++.h>
using ll = long long;
using i64 = ll;
template <class Tp>
Tp dec(Tp &i) {
  return --i;
}
template <class Tp>
Tp inc(Tp &i) {
  return ++i;
}
using namespace std;
#define NO_         \
  {                 \
    cout << "No\n"; \
    return;         \
  }
#define YES_         \
  {                  \
    cout << "Yes\n"; \
    return;          \
  }
void solve(int t_ = 0) {
  i64 n, a, b;
  cin >> n >> a >> b;
  if (a + b > n * 2) NO_;
  if (a == b && a == n) YES_;
  i64 x = n - a - b;
  if (x == 1) NO_;
  if (x > 0) YES_;
  NO_;
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
