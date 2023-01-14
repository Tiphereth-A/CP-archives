#include <bits/stdc++.h>
const int N = 1e5 + 5;
int n, k;
long long f[N] = {1};
int main() {
  std::cin >> n >> k;
  for (int i = 1; i <= n; ++i) {
    for (int j = i - 1; j >= std::max(0, i - k); --j) (f[i] += f[j]) %= 100003;
  }
  std::cout << f[n];
  return 0;
}
