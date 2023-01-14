#include <bits/stdc++.h>
typedef long long ll;
ll n, k;
int main() {
  std::cin >> n >> k;
  ll mid = (n + 1) >> 1;
  if (k <= mid) std::cout << (2 * k - 1);
  else {
    k -= mid;
    std::cout << 2 * k;
  }
  return 0;
}
