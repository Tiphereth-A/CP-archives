#include <bits/stdc++.h>
typedef long long ll;
ll ans;
int n, k;
int main() {
  std::cin >> n;
  for (int i = 1; i <= n; ++i) {
    std::cin >> k;
    ans += k;
  }
  std::cout << ((ans & 1) ? "Alice" : "Bob");
  return 0;
}
