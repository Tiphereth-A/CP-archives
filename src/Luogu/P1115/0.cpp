#include <bits/stdc++.h>
int main() {
  int n;
  std::cin >> n;
  long long ans = 0x8000000000000000, sum = 0;
  for (int tmp, i = 1; i <= n; ++i) {
    std::cin >> tmp;
    ans = std::max(ans, sum += tmp);
    sum = std::max(sum, 0ll);
  }
  std::cout << ans;
  return 0;
}
