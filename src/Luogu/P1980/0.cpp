#include <bits/stdc++.h>
int stat(int num, int digit) {
  int ans = 0;
  for (; num; num /= 10) { ans += (num % 10) == digit; }
  return ans;
}
int main() {
  int n, x;
  long long ans = 0;
  std::cin >> n >> x;
  for (int i = 1; i <= n; ++i) { ans += stat(i, x); }
  std::cout << ans;
  return 0;
}
