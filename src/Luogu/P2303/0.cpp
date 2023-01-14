#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
i64 conv_n_phi(i64 n) {
  i64 ans = n;
  for (i64 i = 2, a; i * i <= n; ++i)
    if (n % i == 0) {
      a = 0;
      while (n % i == 0) {
        ++a;
        n /= i;
      }
      (ans /= i) *= a * (i - 1) + i;
    }
  if (n > 1) (ans /= n) *= n * 2 - 1;
  return ans;
}
int main() {
  i64 n;
  cin >> n;
  cout << conv_n_phi(n);
  return 0;
}
