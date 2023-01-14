#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t_;
  std::cin >> t_;
  for (int i_ = 1, n; i_ <= t_; ++i_) {
    cin >> n;
    for (int border = ceil(sqrt(n)), i = border, cnt = 0; i < n + border;
         i += border)
      for (int j = min(n, i); j > i - border; --j)
        cout << j << " \n"[++cnt == n];
  }
  return 0;
}
