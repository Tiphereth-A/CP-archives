#include <bits/stdc++.h>
using i64 = int64_t;
using namespace std;
void solve(int t_ = 0) {
  int n;
  cin >> n;
  i64 t;
  cin >> t;
  i64 x, y;
  for (int i = 1; i <= n - 2; ++i) cin >> x;
  cin >> x >> y;
  if (x <= y) {
    cout << "Python will never be faster than C++\n";
    return;
  }
  i64 k = x - y;
  cout << "Python 3." << n + (y - t + k) / k << " will be faster than C++\n";
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  solve(i_);
  return 0;
}
